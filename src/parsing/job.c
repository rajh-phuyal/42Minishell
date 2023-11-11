#include "minishell.h"

// t_token	*next_token(t_token	*current) 
// {
// 	t_token	*next;

// 	if (current != NULL) 
// 	{
// 		next = current->next;
// 		return (next);
// 	}
// 	return (NULL); 
// }

// bool	is_token_list(t_token *token)
// {
// 	if (is_name(token))
// }

// bool	is_token_list(t_token *token)
// {

// }

// bool	is_command(t_token *token)
// {
// 	return (is_token_list(token));
// }

// bool	is_job(t_minivault	**minivault)
// {
// 	t_token	*token;

// 	token = next_token((*minivault)->tokens);
// 	if (!token)
// 	{
// 		ft_printf("Expected command"); // probably do this with something else instead of printf
// 		return (false);
// 	}
//     while ((token = next_token(token)) != NULL && !ft_strncmp(token, "|", 1)) 
// 	{
// 		token = next_token(token);
// 		if (token != NULL && is_command(token))
// 			continue ;			
// 		else 
// 		{
// 			perror("Expected command after '|'");
// 			return (false);
// 		}
// 		return (true);
//     }
// 	return (false);
// }

// /*
// function job() {
//     if (nextToken() is command) {
//         while (nextToken() is '|') {
//             if (nextToken() is command) {
//                 continue;
//             } else {
//                 return error("Expected command after '|'");
//             }
//         }
//         return success;
//     } else {
//         return error("Expected command");
//     }
// }

// function command() {
//     while (nextToken() is tokenList) {
//         continue;
//     }
//     return success;
// }

// function tokenList() {
//     if (nextToken() is name) {
//         while (nextToken() is name) {
//             continue;
//         }
//         return success;
//     } else if (nextToken() is arg) {
//         while (nextToken() is arg) {
//             continue;
//         }
//         return success;
//     } else if (nextToken() is redir) {
//         if (nextToken() is redirIn) {
//             if (nextToken() is file) {
//                 continue;
//             } else {
//                 return error("Expected file after redirection");
//             }
//         } else if (nextToken() is redirOut) {
//             if (nextToken() is file) {
//                 continue;
//             } else {
//                 return error("Expected file after redirection");
//             }
//         } else {
//             return error("Invalid redirection");
//         }
//         return success;
//     } else {
//         return error("Invalid token");
//     }
// }

// function redir() {
//     if (nextToken() is redirIn) {
//         return redirIn();
//     } else if (nextToken() is redirOut) {
//         return redirOut();
//     } else {
//         return error("Invalid redirection");
//     }
// }

// function redirIn() {
//     if (nextToken() is '<<') {
//         if (nextToken() is file) {
//             return success;
//         } else {
//             return error("Expected file after '<<'");
//         }
//     } else if (nextToken() is '<') {
//         if (nextToken() is file) {
//             return success;
//         } else {
//             return error("Expected file after '<'");
//         }
//     } else {
//         return error("Invalid input redirection");
//     }
// }

// function redirOut() {
//     if (nextToken() is '>>') {
//         if (nextToken() is file) {
//             return success;
//         } else {
//             return error("Expected file after '>>'");
//         }
//     } else if (nextToken() is '>') {
//         if (nextToken() is file) {
//             return success;
//         } else {
//             return error("Expected file after '>'");
//         }
//     } else {
//         return error("Invalid output redirection");
//     }
// }
// */

// //////////////////////////////////////

// // t_baobab	*command(t_minivault	*minivault)
// // {
// // 	t_baobab	*node;

// // 	node = create_baobab_node(minivault->tokens, CMD);
// // 	if(!node)
// // 		return (NULL);
// // 	// skip to next node somehow
// // 	return (node);
// // }

// // // t_baobab	*job1(t_minivault	*minivault)
// // // {
// // // 	t_baobab	*node;


// // // }

// // t_baobab	*job(t_minivault	*minivault)
// // {
// // 	t_baobab	*node;

// // 	// node = job1(minivault);
// // 	// if (node)
// // 	// 	return (node);
// // 	node = command(minivault);
// // 	if (node)
// // 		return (node);
// // 	return (NULL);
// // }

