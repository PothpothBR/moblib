from pygame.image import load
from pygame import display
class spritesheet:
    
    def __init__(self, filename, cols, rows, surface, handle=0):
        
        self.surface = surface
        
        self.sheet = load(filename)
        
        self.cols = cols
        self.rows = rows
         
        self.totalCellCount = cols * rows
        
        self.rect = self.sheet.get_rect()
        w = self.cellwidth = self.rect.width / cols
        h = self.cellheight = self.rect.height / rows
        
        hw, hh = self.cellCenter = (w / 2, h / 2)
        
        self.cells = list([(index % cols * w, index // cols  * h, w, h) for index in range(self.totalCellCount)])
            
        self.handlePos = list([
            (0,0),   (-hw,0),   (-w,0),
            (0,-hh), (-hw,-hh), (-w,-hh),
            (0,-h),  (-hw,-h),  (-w,-h)])
        
        self.handle = self.handlePos[handle]
        
def draw(self, x_y, cellindex):
    self.surface.blit(self.sheet, (x_y[0] + self.handle[0], x_y[1] + self.handle[1]),self.cells[cellindex])
