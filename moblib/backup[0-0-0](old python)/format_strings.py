def clear_spaces(buffer: str):  # formata o buffer
    sec_buffer = ''
    for i in buffer:  # remove espacos
        if i != ' ':
            sec_buffer += i

    return sec_buffer  # retorn o buffer formatado


def clear_spaces_after(buffer: str):  # formata o buffer

    if buffer[-1] == '\n':  # remove a quebra de linha
        buffer = buffer[:-1]

    for i in buffer:  # remove espacos antes
        if i == ' ':
            buffer = buffer[1:]
        else:
            break

    return buffer  # retorn o buffer formatado


def clear_spaces_before(buffer: str):  # formata o buffer

    if buffer[-1] == '\n':  # remove a quebra de linha
        buffer = buffer[:-1]

    for i in range(len(buffer)):  # remove espacos depois
        if buffer[-1] == ' ':
            buffer = buffer[:-1]
        else:
            break

    return buffer  # retorn o buffer formatado


def format_spaces(buffer: str) -> str:
    sec_buffer = ''
    last = ''
    for i in buffer:  # remove espacos extras
        if i == ' ' and last == ' ':

            continue
        last = i
        sec_buffer += i
    if sec_buffer[-1] == ' ':
        sec_buffer = sec_buffer[:-1]
    if sec_buffer[0] == ' ':
        sec_buffer = sec_buffer[1:]
    return sec_buffer  # retorna o buffer formatado


def add_spaces(string,num):

    if type(string) == str:

        for n in range(1,num+1):

            if len(string) == n:

                string+=(num-n)*' '

    elif type(string) == list:

        for i in range(len(string)):

            if type(string[i]) == list:

                for it in range(len(string[i])):

                    for n in range(1, num + 1):

                        if len(string[i][it]) == n:

                            string[i][it] += (num - n) * ' '

            elif type(string[i]) == str:

                for n in range(1,num+1):

                    if len(string[i]) == n:
                        string[i]+=(num-n)*' '
    return string


def add_spaces_simple(string,num):
    '''retorna a string formatada com o n de espacos nessesitado'''
    for n in range(1, num + 1):
        if len(string) == n:
            string += (num - n) * ' '
    return string