FROM gcc:latest
WORKDIR /app
COPY . .
RUN mkdir -p output
RUN gcc -o relatorio relatorio.c
CMD ["./relatorio"]