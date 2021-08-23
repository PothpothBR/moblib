#biblioteca que simula uma tela usando o terminal
import time,os

class bitmap:
    
    def __init__(self,buffer):
        
        self.flags = []
        
        if type(buffer) == str:
           if buffer[0] == '\n':  # \0
               buffer = buffer.split('\n')[1:]
           else:
               buffer = buffer.split('\n')
           
           max_len = 0
    
           for i in buffer:
               if len(i) > max_len:
                   max_len = len(i)

           for it in range(len(buffer)):
                for n in range(1, max_len + 1):

                   if len(buffer[it]) == n:
                       buffer[it] += (max_len - n) * ' '
             
        for i in range(len(buffer)):
            buffer[i] = list(buffer[i])
        
        back_len = len(buffer[0])
        
        for i in buffer:
            for chr in i:
                if chr == '\n':
                    self.flags.append('not permissed caracter [\n]')
                if chr == '\0':
                    self.flags.append('not permissed caracter [\0]')
                if len(chr) > 1:
                    self.flags.append('incorrect format ['+len(chr)+'] expected <1>')
            if len(i) != back_len or len(i) == 0:
                self.flags.append('bitmap corrupted ['+str(i)+']')
 
            if type(i) != list:
                self.flags.append('incorrect format ['+str(type(i))+'] expected <type: list>')
        if type(buffer) != list:
            self.flags.append('incorrect format ['+str(type(buffer))+'] expected <type: list>')
            
        if len(self.flags) == 0:
            self.buffer = buffer

def new_bitmap(width,heigt,fill):
    return bitmap([fill[0]*width for i in range(height)])
        

class display(bitmap):
    
    def __init__(self,width,height):
        
        self.maxwidth = 118 # 6th = 118, 4x8px = 268
        self.maxheight = 93 #    = 93         = 213
        
        if width < self.maxwidth:
            self.width = width
        else:
            self.width = self.maxwidth
        
        if height < self.maxheight:
            self.height = height
        else:
            self.height = self.maxheight
        
        self.backbuffer = [list(' '*self.width) for i in range(self.height)]
        
        bitmap.__init__(self,self.backbuffer)
        
    def draw_in(self,bitmap,posx,posy):
        
        tam_x = posx+len(bitmap.buffer[0])
        
        for i in range(posy,posy+len(bitmap.buffer)):
            
            for it in range(posx,tam_x):
                self.backbuffer[i][it] = bitmap.buffer[i-posy][it-posx]
    
    def draw_pixel(self,pixel,pos_xy):
        if 0 <= pos_xy[0] < self.width and 0 <= pos_xy[1] < self.height :
            self.backbuffer[pos_xy[1]][pos_xy[0]] = pixel[0]

    def flip(self):
        self.buffer = self.backbuffer
        os.system('clear') or None
        print('|'+'—'*self.width+'|')
                    
        for i in self.buffer:
            print('|',end='')
            for it in i:
                print(it,end='')
            print('|')
            
        print('|'+'—'*self.width+'|')
            
    def clear(self,fill):
        self.backbuffer = []
        for i in range(self.height):
            self.backbuffer.append(list(fill[0]*self.width))