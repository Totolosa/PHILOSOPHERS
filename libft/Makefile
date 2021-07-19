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

NAME			= libft.a
SRCS			= 	ft_memset.c\
					ft_bzero.c\
					ft_memcpy.c\
					ft_memccpy.c\
					ft_memmove.c\
					ft_memchr.c\
					ft_memcmp.c\
					ft_strlen.c\
					ft_isalpha.c\
					ft_isdigit.c\
					ft_isalnum.c \
					ft_isascii.c\
					ft_isprint.c\
					ft_toupper.c\
					ft_tolower.c\
					ft_strchr.c\
					ft_strrchr.c\
					ft_strncmp.c\
					ft_strlcpy.c\
					ft_strlcat.c\
					ft_strnstr.c\
					ft_atoi.c\
					ft_calloc.c\
					ft_strdup.c\
					ft_substr.c\
					ft_strjoin.c\
					ft_strtrim.c\
					ft_split.c\
					ft_itoa.c\
					ft_strmapi.c\
					ft_putchar_fd.c\
					ft_putstr_fd.c\
					ft_putendl_fd.c\
					ft_putnbr_fd.c\
					ft_lstnew.c\
					ft_lstadd_front.c\
					ft_lstsize.c\
					ft_lstlast.c\
					ft_lstadd_back.c\
					ft_lstdelone.c\
					ft_lstclear.c\
					ft_lstiter.c\
					ft_lstmap.c\
					get_next_line.c\
					get_next_line_utils.c\
					calloc_lst.c\
					ft_count_words.c \
					ft_putnbr_base.c \
					ft_add_c_to_str.c \
					ft_pow.c
SRCS_PATH		= srcs/
SRCS_LOC		= $(addprefix $(SRCS_PATH),$(SRCS))
OBJS			= $(SRCS_LOC:srcs/%.c=$(OBJS_DIR)/%.o)
OBJS_DIR		= objs
CC          	= gcc
CFLAGS      	= -g3 -Wall -Werror -Wextra
INCLUDE			= include
RM          	= rm -rf
MKDIR			= mkdir -p

all:			$(NAME)

$(OBJS_DIR):
				$(MKDIR) $(OBJS_DIR)

$(NAME):		$(OBJS_DIR) $(OBJS)
				@printf "\n"
				ar rcs $@ $(OBJS)
				@printf "$(BOLD)${GREEN}--> libft.a generated <--${END}\n"

$(OBJS_DIR)/%.o:srcs/%.c $(INCLUDE)/*.h
				@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@
				@printf "\033[2K\rcompilation $<"

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME) $(OBJS_DIR)

re:				fclean all

.PHONY: 		clean fclean all re
.SILENT:		clean fclean all re ${NAME} $(OBJS_DIR)
