from spritesheet import draw
from random import randint
class paint:
    
    def __init__(self,sheet,sprite,pos):
        
        
        self.pos = [[i[0]*sheet.cellwidth,i[1]*sheet.cellheight] for i in pos]
        self.sheet = sheet
        self.sprite = sprite

        
        
class mapping():
    
    def __init__(self):
        
        self.paints = []
        
    def add(self,sheet,sprite,pos):
        
        self.paints.append(paint(sheet,sprite,pos))

def draw_map(self):
    
    for paint in self.paints:
        for pos in paint.pos:
            draw(paint.sheet,pos,paint.sprite)
        
    