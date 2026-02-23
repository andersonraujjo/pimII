FROM python:3.12-slim
WORKDIR /app
# Não precisamos do COPY se vamos usar volumes para desenvolver, 
# mas vamos deixar por segurança
COPY . . 
# Forçamos o caminho relativo ao WORKDIR
CMD ["python", "main.py"]