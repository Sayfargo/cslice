example-run:
	@echo "Running example..."
	@gcc -Wall -Wextra main.c slice.c -o example
	@./example 