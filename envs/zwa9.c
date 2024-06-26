/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:20:15 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 18:24:17 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_ascii(void)
{
	printf("\033[32m");
	printf("##################################################");
	printf("###########################################################\n");
	printf("#███╗   ███╗ █████╗ ██████╗ ███╗   ██╗███████╗███████╗");
	printf("███████╗      ███████╗██╗  ██╗███████╗██╗     ██╗     #\n");
	printf("#████╗ ████║██╔══██╗██╔══██╗████╗  ██║██╔════╝██╔════╝██");
	printf("╔════╝      ██╔════╝██║  ██║██╔════╝██║     ██║     #\n");
	printf("#██╔████╔██║███████║██║  ██║██╔██╗ ██║█████╗  ███████╗");
	printf("███████╗█████╗███████╗███████║█████╗  ██║     ██║     #\n");
	printf("#██║╚██╔╝██║██╔══██║██║  ██║██║╚██╗██║██╔══╝  ╚════██");
	printf("║╚════██║╚════╝╚════██║██╔══██║██╔══╝  ██║     ██║     #\n");
	printf("#██║ ╚═╝ ██║██║  ██║██████╔╝██║ ╚████║███████╗███████║");
	printf("███████║      ███████║██║  ██║███████╗███████╗███████╗#\n");
	printf("#╚═╝     ╚═╝╚═╝  ╚═╝╚═════╝ ╚═╝  ╚═══╝╚══════╝╚══════╝╚══════╝");
	printf("      ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝#\n");
	printf("##################################################");
	printf("###########################################################\n");
	printf("\033[0m");
}
