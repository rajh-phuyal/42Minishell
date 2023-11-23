/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:36:49 by jalves-c          #+#    #+#             */
/*   Updated: 2023/06/14 16:05:00 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define HEXMIN "0123456789abcdef"
# define HEXMAX "0123456789ABCDEF"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdbool.h>
# include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
int			ft_isalnum(int x);
int			ft_isalpha(int x);
int			ft_isascii(int a);
int			ft_isdigit(int a);
int			ft_isprint(int a);
void		*ft_memset(void *str, int c, size_t n);
size_t		ft_strlcat(char *dest, char *src, size_t size);
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_toupper(int c);
int			ft_tolower(int c);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_calloc(size_t nitems, size_t size);
char		*ft_strdup(const char *s);
int			ft_memcmp(const void *str1, const void *str2, size_t n);
char		*ft_strchr(const char *str, int c);
char		*ft_strrchr(const char *str, int c);
void		*ft_memmove(void *dest, const void *src, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
size_t		ft_strlcpy(char *dest, const char *source, size_t size);
void		*ft_memchr(const void *str, int c, size_t n);
char		*ft_substr(const char *source, unsigned int start, size_t len);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
char		*ft_itoa(int n);
void		ft_putnbr_fd(int n, int fd);
char		*ft_strtrim(char const *str, char const *set);
char		*ft_strjoin(char const *str1, char const *str2);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));	
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char		**ft_split(char const *s, char c);
int			ft_printf(const char *format, ...);
int			ft_printfc(char c);
int			ft_printfselect(char c, va_list args);
int			ft_printfs(char *str);
int			ft_printfn(int n);
int			ft_printfun(unsigned int n);
int			ft_printfx(unsigned long long n, char *base);
int			ft_printfp(unsigned long long n);
char		*get_next_line(int fd);
char		*strjoin(char *line, char *buffer);
bool		ft_manage_buffer(char *buffer);
size_t		ft_strcmp(const char *s1, const char *s2);
void		ft_free_multiple(unsigned int count, ...);
void		ft_free_matrix(char **matrix);
void		ft_print_matrix(char **matrix);

#endif