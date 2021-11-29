
from spritesheet import draw


class animation:
    
    def __init__(self,x_y,rangeOfCells,startCell=1,direction=0,cellInterval=0,stepCell=0):
        
        if direction == 2 or direction == 'flip':
            self.count = startCell
        else:
            self.count = startCell-2
        self.start = startCell-1
        self.end = (startCell-1)+ rangeOfCells-1
        self.x_y = [x_y[0],x_y[1]]
        self.interval = cellInterval+1
        self.jump = 0
        self.direction = direction
        self.rangeOfCells = rangeOfCells-1
        self.flip = -(stepCell+1)
        self.step = stepCell+1
        
        
        #             nome|quant d/sprits|sprit d/inicio|direcao|intervalo entre sprites

def mod_anim_start(self,start):
        
        self.start = start -1
        if self.direction == 2 or self.direction == 'flip':
            self.count = start
        else:
            self.count = start -2 # -1 para contagem de vetor, -1 para o inicio
        self.end = (start -1) + self.rangeOfCells -1

def mod_anim_range(self,range):
        self.rangeOfCells = range - 1
        self.end = self.start + range - 1

def mod_anim_direction(self,direct):
        self.direction = direct
        
def mod_anim_step(self,step):
        self.step = step+1

def mod_anim_interval(self,interval):
        self.interval = interval

def mod_anim_pos(self,x_y):
        self.x_y[0],self.x_y[1] = x_y

def anim_normal(self):
       
        self.count += self.step
           
        if self.count > self.end:
            self.count = self.start
         
        return self.count
        
def anim_inverse(self):
        
        self.count -= self.step
        
        if self.count < self.start:
            self.count = self.end
       
        return self.count

def anim_flip(self):
        
        if self.count <= self.start or self.count >= self.end:
            
            self.flip *= -1
            
        self.count += self.flip
           
  
        return self.count
        
def anim(self):

        if self.jump > 1:
            self.jump -= 1
            return self.count
        else:
            self.jump = self.interval
            if self.direction == 0 or self.direction == 'normal':
                return anim_normal(self)
            
            elif self.direction == 1 or self.direction == 'inverse':
                return anim_inverse(self)
            
            elif self.direction == 2 or self.direction == 'flip':
                return anim_flip(self)
    
def draw_anim(self,spritesheet):
        draw(spritesheet,self.x_y,anim(self))
