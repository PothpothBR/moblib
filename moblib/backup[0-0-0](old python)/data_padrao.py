from format_strings import add_spaces
class personagem(object):
    # variaveis com 20 caracteres por ordem de insercao
            # nome [0]
    i20 = [ 'i20[0]',
    
            # caracteristicas [1]
            ['i20[1][0]', # vida [1][0]
             'i20[1][1]', # dano [1][1]
             'i20[1][2]', # energia [1][2]
             'i20[1][3]', # esquiva [1][3]
             'i20[1][4]'],# escudo [1][4]
    
            # escalamento por nivel [2]
            ['i20[2][0]',  # vida [2][0]
             'i20[2][1]',  # dano [2][1]
             'i20[2][2]',  # energia [2][2]
             'i20[2][3]',  # esquiva [2][3]
             'i20[2][4]'], # escudo [2][4]
    
            # abilidades [3] - [4] - [5] - [6] - [7] - [8]
             ['i20[3][0]', # primeira [3][0]
              'i20[3][1]', # [3][1]
              'i20[3][2]'],# [3][2]
    
             ['i20[4][0]', # segunda [4][0]
              'i20[4][1]', # [4][1]
              'i20[4][2]'],#[4][2]
    
             ['i20[5][0]', # terceira [5][0]
              'i20[5][1]', # [5][1]
              'i20[5][2]'],# [5][2]
    
             ['i20[6][0]', # quarta [6][0]
              'i20[6][1]', # [6][1]
              'i20[6][2]'],# [6][2]
    
             ['i20[7][0]', # quinta [7][0]
              'i20[7][1]', # [7][1]
              'i20[7][2]'],# [7][2]
    
             ['i20[8][0]', # passiva [8][0]
              'i20[8][1]', # [8][1]
              'i20[8][2]', # [8][2]
              'i20[8][3]', # [8][3]
              'i20[8][4]', # [8][4]
              'i20[8][5]', # [8][5]
              'i20[8][6]', # [8][6]
              'i20[8][7]']]#[8][7]
    
    # variaveis com 12 caracteres por ordem de insercao
           # classe
    i12 = ['i12[0]',
    
           # classe de itens
           'i12[1]', # superiores
           'i12[2]',
           'i12[3]',
           'i12[4]',
           'i12[5]',
           'i12[6]',
    
           'i12[7]', # inferiores
           'i12[8]',
           'i12[9]',
           'i12[10]',
           'i12[11]',
           'i12[12]',
           'i12[13]']
    
    # variaveis com 6 caracteres por ordem de insercao
          # id
    i6 = ['i6[0]',
    
          # caracteristicas
          'i6[1]', # recuperacao de vida
          'i6[2]', # recuperacao de energia
    
          # escalamento por nivel
          'i6[3]', # recuperacao de vida
          'i6[4]']# recuperacao de energia
    
    i20 = add_spaces(i20, 20)
    i12 = add_spaces(i12, 12)
    i6 = add_spaces(i6, 6)
ps = personagem()