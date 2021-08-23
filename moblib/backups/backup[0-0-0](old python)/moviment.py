from os import system
from time import sleep
from math import ceil
from pygame.draw import rect,line,circle

class moviment:
    
    def __init__(self,x_y):
       
        self.x,self.y = x_y
        self.d_h = 0
        self.stop = True
        self.f_x,self.f_y = x_y
        self.f_h = 0
        
        self.d_x = 0
        self.d_y = 0
        
        self.vu_x = 0
        self.vu_y = 0
        
        self.vel = 0
        self.dir = ['x','xx']

def hip(x_y):
    return (x_y[0]**2+x_y[1]**2)**0.5

def mod_vel(self,vel):
    
    self.vel = vel
    if self.d_x:
        self.vu_x = self.vel/self.d_h*self.d_x
        self.vu_y = self.vel/self.d_h*self.d_y
    

def set_dir(self,x_y,vel):
    
    
    if x_y[0] == self.x and x_y[1] == self.y:
        return None
    
    self.vel = vel
    
    self.stop = False
    
    self.d_x = x_y[0]-self.x
    self.d_y = x_y[1]-self.y
    
    self.f_x,self.f_y = x_y
    self.f_h = hip(x_y)
    self.d_h = hip([self.d_x,self.d_y])
    self.vu_x = self.vel/self.d_h*self.d_x
    self.vu_y = self.vel/self.d_h*self.d_y
    
    x,y = self.d_x,self.d_y
    
    mod_dir = []
    
    
    if y > x > 0:
      mod_dir.append('s')
    if x > y > 0:
      mod_dir.append('d')
    if y < x < 0:
     mod_dir.append('w')
    if x < y < 0:
      mod_dir.append('a')
    if 0 < -x < y:
      mod_dir.append('s')
    elif 0 < -y < x:
      mod_dir.append('d')
    elif 0 > -x > y:
      mod_dir.append('w')
    elif 0 > -y > x:
      mod_dir.append('a')
    
    if y > 0 and x > 0:
      mod_dir.append('sd')
    if y < 0 and x < 0:
      mod_dir.append('wa')
    if y > 0 and x < 0:
      mod_dir.append('sa')
    if y < 0 and x > 0:
      mod_dir.append('wd')
      
    if mod_dir != [] and len(mod_dir) == 2:
        self.dir = mod_dir
        
        
      
def run(self):
    
    self.x += self.vu_x
    self.y += self.vu_y
    
    if self.vu_x > 0 and self.x >= self.f_x:
        self.x = self.f_x
        self.stop = True
    elif self.vu_x < 0 and self.x <= self.f_x:
        self.x = self.f_x
        self.stop = True   
    if self.vu_y > 0 and self.y >= self.f_y:
        self.y = self.f_y
        self.stop = True
    elif self.vu_y < 0 and self.y <= self.f_y:
        self.y = self.f_y
        self.stop = True
    return [ceil(self.x),ceil(self.y)]    
    
 
def debug(tela,obj):
  line(tela,(155,155,155),(obj.x,obj.y),(obj.f_x,obj.f_y),4)
  
  
  if obj.stop:
      c_stop = (0,0,255)
  else:
      c_stop = (255,0,0)
      
  rect(tela,c_stop,[obj.f_x-5,obj.f_y-5,10,10])
  
  
  
  circle(tela,(0,0,255),(obj.x,obj.y),50,4)
  
  c_mov_w = (0,0,255)
  c_mov_s = (0,0,255)
  c_mov_a = (0,0,255)
  c_mov_d = (0,0,255)
  
  x = obj.x - obj.f_x
  y = obj.y - obj.f_y
  
  if y > 0 and x > 0:
      c_mov_s = (0,255,0)
      c_mov_d = (0,255,0)
  elif y < 0 and x < 0:
      c_mov_w = (0,255,0)
      c_mov_a = (0,255,0)
  elif y > 0 and x < 0:
      c_mov_s = (0,255,0)
      c_mov_a = (0,255,0)
  elif y < 0 and x > 0:
      c_mov_w = (0,255,0)
      c_mov_d = (0,255,0)
      
  if y > x > 0:
      c_mov_s = (255,0,0)
  elif x > y > 0:
      c_mov_d = (255,0,0)
  elif y < x < 0:
      c_mov_w = (255,0,0)
  elif x < y < 0:
      c_mov_a = (255,0,0)
  elif 0 < -x < y:
      c_mov_s = (255,0,0)
  elif 0 < -y < x:
      c_mov_d = (255,0,0)
  elif 0 > -x > y:
      c_mov_w = (255,0,0)
  elif 0 > -y > x:
      c_mov_a = (255,0,0)
  
  rect(tela,c_mov_w,[obj.x-2,obj.y,4,50])
  rect(tela,c_mov_s,[obj.x-2,obj.y-55,4,50])
  rect(tela,c_mov_a,[obj.x,obj.y-2,50,4])
  rect(tela,c_mov_d,[obj.x-55,obj.y-2,50,4])
      
