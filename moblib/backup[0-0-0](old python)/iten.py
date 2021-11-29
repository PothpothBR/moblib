
class items(object):
    
    classes = [
    'guerreiro',
    'tank',
    'paladino',
    'curandeiro',
    'xama',
    'mago', 
    'arqueiro',
    'pistoleiro',
    'sniper'
    'fuzileiro'
    'ladino',
    'assasino'
    'ninja',
    'espadachin'
        ]
    
    nivel_max = 30
    
    missoes = 5
    
    abilidades_por_classe = [
        ['forca',[
            'espadachin',
            'guerreiro',
            'tank',
            'paladino'
            ]
        ],
        ['defesa',[
            'guerreiro',
            'tank',
            'paladino',
            'curandeiro'
            ]
        ],
        ['escudo',[
            'tank',
            'paladino',
            'curandeiro',
            'xama',
            
            ]
        ],
        ['',[ # nao foi feito
            'paladino',
            'curandeiro',
            'xama',
            'mago'
            ]
        ]
        
    ]

class player(items):
    
    classe = ''
    bolsa = []
    nivel = 0
    xp_acumulado = 0
    missoes_completas = 0
    abilidades = []
    ataques_basicos = []
    runas = []
    passivas = []
    arma = ''
    elmo = ''
    peitoral = ''
    calca = ''
    botas = ''
    luvas = ''
    aneis = ''
    escudo = ''
    pergaminhos = []
    
class tela_criacao(object):
    
    def __init__():
        pass
    def tela():
        print('''
    |———————————————————————————————————————————————|
    |                    |                          |
    |  CARACTERISTICAS:  |  NOME: ****************  |
    |                    |                          |
    |————————————————————|——————————————————————————|
    |                               |               |
    |  vida...: ****                |    ITENS:     |
    |                               |               |
    |  dano...: ****                |———————————————|
    |                               |               |
    |  defesa.: ****                |  cabeca: 1,2  |
    |                               |               |
    |                               |               |
    |  esquiva: ****                |  maos: 3,4,5  |
    |                               |               |
    |                               |               |
    |  energia: ****                |  peito: 7,8,9 |
    |                               |               |
    |                               |               |
    |  recuperacao de energia: ***  |  pernas: 1,5  |
    |                               |               |
    |                               |               |
    |  recuperacao de vida...: ***  |  pes: 12,13   |
    |                               |               |
    |                               |               |
    |———————————————————————————————————————————————|
    |  numeracao: 1-*** 2-*** 3-*** 4-*** 5-***
        ''')
    
tt = tela_criacao
tt.tela()