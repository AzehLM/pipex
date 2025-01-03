# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    pipex.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/29 13:53:50 by gueberso          #+#    #+#              #
#    Updated: 2025/01/03 14:18:52 by gueberso         ###   ########.fr        #
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
	pipex_utils \

SRCBONUS += $(addprefix $(BONUSDIR), $(addsuffix .c, $(BONUSSRC)))

override BONUSSRC		:= \
	pipex \
	pipex_utils \
