/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 20:18:34 by jtahirov          #+#    #+#             */
/*   Updated: 2018/03/12 20:56:28 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "../libft/libft.h"
# include <stdbool.h>
# include <stdint.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# define LS_USAGE "usage: ls [-RSafloprt] [file ...]"
# define MAKE_NULL(x) x = NULL;
# define M_N(x) x = NULL
# define MAKE_NULL2(x, y) MAKE_NULL(x) M_N(y)
# define MAKE_NULL3(x, y, z) MAKE_NULL(x) MAKE_NULL(y) M_N(z)

# define FILES  1
# define DIRS   2
# define BOTH	3

extern			int g_optind;
enum			e_sort_worker{pivot, previous, current, tail, all};
enum			e_recur{new_head, new_end};

/*
** -------------------- Flags description ----------------------------
** -l -> long_format (print all info from t_filedir)
** -R -> Recursion (look into all subdirs and print relevant information)
** -a -> show files with '.' as a first char in filename
**				(by default dot files has no-show status)
** -r ->Reverse sort(print your objects in reverse order after you sorted it)
**						(maybe use ft_lstmap or smth like that)
** -t -> Time sort (same as -r but use different sort)
** -S -> Size sort (from big to small by default)
** -f -> no sort print them as they come with .[filename]
** -o -> print in long_format, but omit the group id
** -p -> print '/' after each file if that file is a directory.
** -------------------------------------------------------------------
*/

typedef struct	s_lsflags
{
	bool	l;
	bool	recur;
	bool	a;
	bool	r;
	bool	t;
	bool	size;
	bool	f;
	bool	o;
	bool	p;
	bool	lex;
}				t_lsflags;

typedef struct	s_file
{
	bool			isfile;
	char			*path;
	char			*filename;
	char			*link_path;
	struct stat		stat;
}				t_file;

typedef struct	s_train
{
	t_file			file;
	struct s_train	*next;
}				t_train;

typedef struct	s_lsmain
{
	bool		multiple_arg;
	int32_t		max_digit_link;
	int32_t		max_digit_size;
	int32_t		max_ownername_len;
	int32_t		max_groupname_len;
	int32_t		max_major;
	int32_t		max_minor;
	t_lsflags	flag;
}				t_lsmain;

typedef int		(*t_lsfunc)(t_train *, t_train *);

/*
** Utillity t_lsfunctions
*/
void			ft_lsusage(void);
int				ft_isfile(const char *name);
/*
** Parsing and geting data
*/
int				ft_lsparse_flags(t_lsmain *main, int argc, char **argv);
t_train			*ft_lsget_args(t_lsmain *main, int argc, char **argv);
t_train			*ft_lsfind_dir(t_train *args);
void			ft_lsget_max(t_lsmain *main, t_train *args);
char			*ft_lsget_mode(t_file *file);
char			*ft_lsget_ownername(struct stat *stat);
char			*ft_lsget_groupname(struct stat *stat);
int				ft_lsget_dayofmonth(struct stat *stat);
char			*ft_lsget_time(struct stat *stat);
int				ft_lsget_total(t_train *args);
/*
** Main logic
*/
void			ft_lsmain(t_lsmain *main, int argc, char **argv);
void			ft_lsprint(t_train *input, t_lsmain *main);
void			ft_lshandle_args(t_train **args, t_lsmain *main);
void			ft_lshandle_dirs(t_train **dirs, t_lsmain *main, bool first);
void			ft_lshandle_dir(t_train *dir, t_lsmain *main);
/*
** Sort t_lsfunctions
*/
void			ft_lssort(t_train **root, t_lsmain *main);
t_train			*ft_lssort_recur(t_train *head, t_train *tail,
									t_lsfunc sort_t_lsfunction);
int				ft_lssort_file(t_train *element1);
int				ft_lssort_lexicographical(t_train *node, t_train *node2);
int				ft_lssort_time(t_train *node, t_train *node2);
int				ft_lssort_size(t_train *node, t_train *node2);
int				ft_lssort_lexrev(t_train *node, t_train *node2);
int				ft_lssort_timerev(t_train *node, t_train *node2);
int				ft_lssort_sizerev(t_train *node, t_train *node2);
t_lsfunc		ft_getsort(t_lsflags flag);

/*
** Train t_lsfunction
*/
t_train			*ft_lstrain_create(char *filename, char *pathname);
void			ft_lstrain_add(t_train **root, t_train *new_train);
t_train			*ft_trainget_tail(t_train *root);
void			ft_printf_node(t_train *node);
t_train			*ft_trainfiles(t_train **current, int8_t mode, t_train **buf);
int				ft_trainget_files(t_train *current);
int				ft_trainget_dir(t_train *current);
void			ft_lssort(t_train **root, t_lsmain *main);
void			ft_traindel(t_train **root);
t_train			*ft_train_pop(t_train **root);
void			ft_trainfree(t_train **train);

#endif
