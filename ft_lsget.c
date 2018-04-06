/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsget.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 09:05:40 by jtahirov          #+#    #+#             */
/*   Updated: 2018/02/19 00:50:58 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

static char		ft_lsget_modehelp(mode_t mode)
{
	if (S_ISDIR(mode))
		return ('d');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISFIFO(mode))
		return ('p');
	else if (S_ISSOCK(mode))
		return ('s');
	return ('-');
}

static char		ft_lsget_modeacl(char *path)
{
	int		xattrs;
	acl_t	acl;

	xattrs = (int)listxattr(path, NULL, 1, XATTR_NOFOLLOW);
	if (xattrs > 0)
		return ('@');
	else
	{
		acl = acl_get_file(path, ACL_TYPE_EXTENDED);
		return ((acl != NULL) ? '+' : '\0');
	}
}

char			*ft_lsget_mode(t_file *file)
{
	char		*filemode;
	struct stat *stat;

	filemode = ft_strnew(11);
	stat = &file->stat;
	*filemode++ = ft_lsget_modehelp(stat->st_mode);
	*filemode++ = (stat->st_mode & S_IRUSR) ? 'r' : '-';
	*filemode++ = (stat->st_mode & S_IWUSR) ? 'w' : '-';
	*filemode++ = (stat->st_mode & S_IXUSR) ? 'x' : '-';
	*filemode++ = (stat->st_mode & S_IRGRP) ? 'r' : '-';
	*filemode++ = (stat->st_mode & S_IWGRP) ? 'w' : '-';
	*filemode++ = (stat->st_mode & S_IXGRP) ? 'x' : '-';
	*filemode++ = (stat->st_mode & S_IROTH) ? 'r' : '-';
	*filemode++ = (stat->st_mode & S_IWOTH) ? 'w' : '-';
	if (stat->st_mode & S_ISVTX)
		*filemode++ = 't';
	else
		*filemode++ = (stat->st_mode & S_IXOTH) ? 'x' : '-';
	*filemode++ = ft_lsget_modeacl((file->path) ? file->path : file->filename);
	return (filemode - 11);
}

char			*ft_lsget_ownername(struct stat *stat)
{
	struct passwd *pwd;

	pwd = getpwuid(stat->st_uid);
	return (pwd->pw_name);
}

char			*ft_lsget_groupname(struct stat *stat)
{
	struct group *grp;

	grp = getgrgid(stat->st_gid);
	return (grp->gr_name);
}
