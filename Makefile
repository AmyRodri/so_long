NAME        = so_long

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDE     = -I libft/srcs/includes -I include

RM          = rm -f
RUNLIB      = -C libft

# Diretórios
SRCSDIR         = srcs
OBJDIR          = objs

# Fontes normais
SRCS = main.c		\
	   utils.c		\
	   check_map.c	\
	   read_map.c	

# Adiciona prefixo do diretório
SRCS := $(addprefix $(SRCSDIR)/, $(SRCS))

# Objetos
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

# Lib
LIBFT = libft/libft.a

# ---------- Regras ----------
all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBFT) -o $(NAME)

# regra para compilar arquivos normais
$(OBJDIR)/%.o: $(SRCSDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# cria a pasta objs se não existir
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	$(MAKE) $(RUNLIB)

clean:
	$(RM) -r $(OBJDIR)
	$(MAKE) clean $(RUNLIB)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean $(RUNLIB)

re: fclean all

.PHONY: all clean fclean re
