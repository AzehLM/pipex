# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    pipex.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/29 13:53:50 by gueberso          #+#    #+#              #
#    Updated: 2025/01/07 16:02:33 by gueberso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR), $(SRC))
override SRCSBONUS	= $(addprefix $(SRCSDIR), $(SRCBONUS))

override MANDATORYDIR	:= mandatory/
override BONUSDIR		:= bonus/

SRC	+= $(addprefix $(MANDATORYDIR), $(addsuffix .c, $(MANDATORYSRC)))

override MANDATORYSRC	:= \
	pipex \
	utils \

SRCBONUS += $(addprefix $(BONUSDIR), $(addsuffix .c, $(BONUSSRC)))

override BONUSSRC		:= \
	child \
	command \
	init \
	pipex_bonus \
	utils_bonus \
