# ---------- Configurações ----------
NAME        = so_long

GREEN       = \033[0;32m
YELLOW      = \033[0;33m
NC          = \033[0m

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDE     = -I libft/srcs/includes -I include

RM          = rm -rf
RUNLIB      = -C libft

# Diretórios
SRCSDIR     = srcs
OBJDIR      = objs

# Fontes
SRCS = main.c					\
	   utils.c					\
	   check_map.c				\
	   read_map.c				\
	   check_reachability.c		

# Adiciona prefixo do diretório
SRCS := $(addprefix $(SRCSDIR)/, $(SRCS))

# Objetos
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

# Lib
LIBFT = libft/libft.a

# ---------- Regras ----------
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBFT) -o $(NAME)
	@printf "$(GREEN)🎉 Executável $(NAME) criado com sucesso!$(NC)\n"

# Compilar objetos
$(OBJDIR)/%.o: $(SRCSDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "$(YELLOW)⚙️ Compilando %s -> %s$(NC)\n" "$<" "$@"

# Criar pasta objs se não existir
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Compilar libft silenciosamente
$(LIBFT):
	@$(MAKE) $(RUNLIB) -s
	@printf "$(GREEN)✅ Libft compilada com sucesso$(NC)\n"

# Limpeza
clean:
	@$(RM) $(OBJDIR)
	@$(MAKE) clean $(RUNLIB) -s
	@printf "$(YELLOW)🧹 Objetos limpos$(NC)\n"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean $(RUNLIB) -s
	@printf "$(YELLOW)🗑️ Executável removido$(NC)\n"

re: fclean all

.PHONY: all clean fclean re
