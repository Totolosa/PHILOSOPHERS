ERASE   = \033[2K\r
GREY    = \033[30m
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
PINK    = \033[35m
CYAN    = \033[36m
WHITE   = \033[37m
END     = \033[0m
BOLD    = \033[1m
UNDER   = \033[4m
SUR     = \033[7m

NAME_PHILO		= philo
NAME_BONUS		= philo_bonus
DIR_SRCS		= srcs
DIR_PHILO		= $(DIR_SRCS)/philo
DIR_BONUS		= $(DIR_SRCS)/philo_bonus
DIR_UTILS		= $(DIR_SRCS)/utils
SRCS_PHILO		=	philo.c 
SRCS_BONUS		= 	#philo_bonus.c 
SRCS_UTILS		=	quit_prog.c \
					ft_atoi_philo.c
LST_UTILS		= $(addprefix $(DIR_UTILS)/,$(SRCS_UTILS))
LST_PHILO		= $(addprefix $(DIR_PHILO)/,$(SRCS_PHILO))
LST_BONUS		= $(addprefix $(DIR_BONUS)/,$(SRCS_BONUS))
OBJS_UTILS		= ${LST_UTILS:srcs/%.c=$(DIR_OBJS)/%.o} 
OBJS_PHILO		= ${LST_PHILO:srcs/%.c=$(DIR_OBJS)/%.o} ${OBJS_UTILS}
OBJS_BONUS		= ${LST_BONUS:srcs/%.c=$(DIR_OBJS)/%.o} ${OBJS_UTILS}
DIR_OBJS		= objs
CC				= gcc -pthread
# CFLAGS			= -Wall -Werror -Wextra
CFLAGS			=  -g3 -Wall -Werror -Wextra -fsanitize=address
INCLUDE			= -Iinclude -I${LIBFT}/include
RM				= rm -rf
MKDIR			= mkdir -p
LIBFT			= libft

all:			libft ${NAME_PHILO} #$(NAME_BONUS)

$(DIR_OBJS):
				$(MKDIR) $@

libft: 
				make -C ${LIBFT}

${NAME_PHILO}:	libft/libft.a ${DIR_OBJS} ${OBJS_PHILO}
				${CC} ${CFLAGS} ${INCLUDE} ${OBJS_PHILO} -L ${LIBFT} -lft -o ${NAME_PHILO}
				echo "$(BOLD)${GREEN}$(ERASE)--> PHILO generated <--${END}"

${NAME_BONUS}:	libft/libft.a ${DIR_OBJS} ${OBJS_BONUS}
				${CC} ${CFLAGS} ${INCLUDE} ${OBJS_BONUS} -L ${LIBFT} -lft -o ${NAME_BONUS}
				echo "$(BOLD)${GREEN}--> PHILO_BONUS generated <--${END}"

$(DIR_OBJS)/%.o:$(DIR_SRCS)/%.c include/*.h
				$(MKDIR) $(dir $@)
				${CC} ${CFLAGS} $(INCLUDE) -c  $< -o $@

clean:
				${RM} ${OBJS_PHILO} ${OBJS_BONUS}
				make clean -C $(LIBFT)

fclean:			clean
				${RM} $(DIR_OBJS) $(NAME_PHILO) ${NAME_BONUS}
				make fclean -C $(LIBFT)
				echo "${RED}XXXXX CLEAN XXXXX${END}"

re:				fclean all

.PHONY: 		clean fclean all re compil libft
.SILENT:		clean fclean all re compil libft ${OBJS_PHILO} ${OBJS_BONUS} $(NAME_PHILO) ${NAME_BONUS} $(DIR_OBJS)
