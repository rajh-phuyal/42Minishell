/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:15:19 by rphuyal           #+#    #+#             */
/*   Updated: 2023/07/25 22:20:28 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* for gnl */
# define HEXMIN "0123456789abcdef"
# define HEXMAX "0123456789ABCDEF"
# define DECIMAL "0123456789"

/* colors */
# define BOLD "\033[1m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define YELLOW "\x1b[33m"
# define CYAN "\x1b[36m"
# define UNDERLINE "\x1b[4m"
# define RESET_COLOR "\033[0m"

/* if the buffersize is not manully defined during
compilation which probably is not*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdbool.h>

/*
structure for nodes to contain a content pointer
an a link to the next node
*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* functions that handel individual chars*/
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_toupper(int ch);
int		ft_tolower(int ch);

/* functions that puts number, chars, or strings in a given fd*/
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);

/* functions that handel memory operations*/
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nitems, size_t size);
void	*ft_memchr(const void *str, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *m1, const void *m2, size_t n);

/* functions that manipulate, concatiante, compare, etc with strings*/
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
char	*ft_strdup(const char *s);
int		ft_strlen(const char *str);
int		ft_splitlen(char **splited);
int		ft_emptystr(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlcat(char *dest, char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t num);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/* functions for linked list operations */
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* prototypes for printf */
int		ft_putstr(char *str);
char	*ft_strrev(char *str);
char	*ft_getintstr(long n);
int		ft_putcharprintf(char c);
int		ft_printf(const char *str, ...);
int		get_hex_len(unsigned long long n);
char	*ft_gethexstr(unsigned long long num, char *base);

/* function prototypes for getnextline*/
size_t	getuntilnl(char *str);
char	*get_next_line(int fd);
void	clear_buffer(char *buffer);
int		manage_buffer(char *buffer);
int		create_line(char **line_ptr, char *buffer, size_t size);

#endif
