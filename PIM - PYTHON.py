from time import sleep
#para verificar a existencia do arquivo csv posteriormente
import os
#importando a bilbioteca csv, formato do qual os dados serão salvos
import csv

#função para carregar os dados csv, ler o arquivo e retornar a lista de alunos
def carregar_dados_csv(nome_arquivo):
    if os.path.exists(nome_arquivo) and os.path.getsize(nome_arquivo) > 0:
        with open(nome_arquivo, 'r', newline='', encoding='utf-8') as f:
            reader = csv.reader(f)

            try:
                #pula a primeira linha do csv, que é o cabeçalho, com as infos de nome, materia etc
                next(reader)
                #retorna lista vazia caso só haja o cabeçalho sem dados
            except StopIteration:
                return []
            
            lista_alunos_carregada = []

            for row in reader:
                if len(row) == 7:
                    #transforma os dados de texto em dados python, aqui em formato de dicionario 
                    lista_alunos_carregada.append({
                        'materia': row[0],
                        'nome': row[1],
                        'ra': row[2],
                        'turma': row[3],
                        'notas': [float(row[4]), float(row[5])],
                        'media': float(row[6])
                    })
            return lista_alunos_carregada
    return []


#definindo as listas / dicionarios
dicion = {}
#ja inicializa a lista carregando o csv, definido pela função carregar_dados_csv
lista_alunos = carregar_dados_csv('alunos.csv')
notas = []
opcoes_materias = {'0':'ENGENHARIA DE SOFT AGIL', '1':'PYTHON','2':'C', '3':'ANALISE DE PROJETOS'}
cabecalho_csv = ['materia', 'nome', 'ra', 'turma', 'nota1', 'nota2', 'media']

#definindo cores
VERMELHO = '\033[91m'
VERDE = '\033[92m'
AZUL = '\033[94m'
NEGRITO = '\033[1m'
RESET = '\033[0m'
AMARELO = '\033[93m'
ITALICO = '\033[3m'


print(f"""{AMARELO}{ITALICO}{NEGRITO}UNIVERSIDADE PAULISTA{RESET}
{NEGRITO}{ITALICO}CADASTRO DE ALUNOS{RESET}""")
print('\n')


            
#loop de validação de materia
while True:
    while True:
        escolha_materia = input(f"""Escolha a disciplina que será cadastrada de acordo com sua numeração: 
                                    0 - ENGENHARIA DE SOFT AGIL
                                    1 - PYTHON
                                    2 - C
                                    3 - ANALISE DE PROJETOS
                                    99 - {NEGRITO}{VERMELHO}SAIR DO PROGRAMA{RESET}
                                    >>> """)
        if escolha_materia in opcoes_materias:
            dicion['materia'] = opcoes_materias[escolha_materia]
            break
        elif escolha_materia == '99':
            break
        else:
            print(f'{VERMELHO}Por favor, selecione uma das matérias válidas.{RESET}')
    if escolha_materia == '99':
        break
    
#loop de dados necessários para o cadastro do aluno 
    print('\n')
    while True:
        while True:
            dicion['nome'] = input('Cadastre o nome do aluno: ')
            dicion['ra'] = input('Cadastre o RA: ').upper()
            dicion['turma'] = input('Cadastre a turma: ').upper()
            print(f'{ITALICO}{NEGRITO}{dicion['nome']}, {dicion['ra']}, {dicion['turma']}{RESET}')
            while True:
                resp = input(f'{VERDE}Confere os dados? [S/N]: {RESET}').lower()
                if resp == 's':
                    break
                elif resp == 'n':
                    dicion.clear()
                    dicion['materia'] = opcoes_materias[escolha_materia]
                    break
                else:
                    print(f'{VERMELHO}Opção inválida.{RESET}')
            if resp == 's':
                break
        if resp =='s':
            break

   
   #laço para validação das notas
    while True:
        try:
            nota1 = float(input('Nota da NP1: '))
            if nota1 <0 or nota1 > 10:
                print('Nota fora do intervalo (0 a 10).')
            else: 
                break
        except ValueError:
            print(f'{VERMELHO}Entrada inválida.{RESET}')
        
    while True:
        try:
            nota2 = float(input('Nota da NP2: '))
            if nota2 <0 or nota2 >10:
                print('Nota fora do intervalo (0 a 10).')
            else:
                break
        except ValueError:
            print(f'{VERMELHO}Entrada inválida.{RESET}')

        
#calculo de media, inclusão da lista e dicionario, limpa lista e dicionario        
    media_simples = (nota1 + nota2) / 2
    notas.append(nota1)
    notas.append(nota2)
    dicion['media'] = media_simples
    dicion['notas'] = notas.copy()
    lista_alunos.append(dicion.copy())
    dicion.clear()
    notas.clear()

#loop de verificação
    while True:
        escolha_usuario = input('Deseja continuar a adicionar alunos? [S/N]: ').lower()
        if escolha_usuario in 'sn':
            break
        else:
            print(f'{VERMELHO}Digite uma opção válida.{RESET}')
    if escolha_usuario == 'n':
        break


#separando os alunos por disciplina
alunos_por_disciplina = {}

#loop para adicionar
for aluno in lista_alunos:
    materia = aluno['materia']
    if materia not in alunos_por_disciplina:
        alunos_por_disciplina[materia] = []
    alunos_por_disciplina[materia].append(aluno)

print('\n')

#loop para salvar cada materia no csv
for materia, lista_alunos_disc in alunos_por_disciplina.items():
    nome_arquivo = f"{materia}.csv"
    with open(nome_arquivo, 'w', newline='',encoding='utf-8') as arquivo_csv:
        writer = csv.writer(arquivo_csv)
        writer.writerow(cabecalho_csv)
        for aluno in lista_alunos_disc:
            linha = [
            aluno['materia'],
            aluno['nome'],
            aluno['ra'],
            aluno['turma'],
            aluno['notas'][0],
            aluno['notas'][1],
            aluno['media']
        ]
            writer.writerow(linha)
        print(f'{VERDE}{NEGRITO}Dados da disciplina {materia} salvos em {nome_arquivo} com sucesso.{RESET}')


#salva o csv com todos os dados 
with open('alunos.csv','w',newline='', encoding='utf-8') as arquivo_csv:
    writer = csv.writer(arquivo_csv)
    writer.writerow(cabecalho_csv)
    for aluno in lista_alunos:
        linha = [
            aluno['materia'],
            aluno['nome'],
            aluno['ra'],
            aluno['turma'],
            aluno['notas'][0],
            aluno['notas'][1],
            aluno['media']
        ]
        writer.writerow(linha)
    
print('\n')
print(f'{AZUL}{NEGRITO}SAINDO DO SISTEMA...{RESET}')
sleep(2)
print('\n')

#prints para verificação somente
print(f'{ITALICO}{NEGRITO}LISTA DE ALUNOS COM TODAS AS MATÉRIAS: {RESET}')
print(lista_alunos)
print(f'{ITALICO}{NEGRITO}ALUNOS POR DISCIPLINA:  {RESET}')
print(alunos_por_disciplina)
