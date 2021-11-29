# adicionando a biblioteca pygame

import pygame
from pygame.locals import *
from time import sleep as slp
from math import sqrt

import spritesheet as ss
import moviment as mov
import animation as anm
import events as ev
import mapping as map

mov_pers = mov.moviment((400,400))

pygame.init()  
  
tela = pygame.display.set_mode((400,600))

pers = ss.spritesheet('rpgsprites//actor_2x.png',12,8,tela,7)
arm = ss.spritesheet('rpgsprites//armas.png',8,8,tela,0)
efect = ss.spritesheet('rpgsprites//efects//12_nebula_spritesheet.png',8,8,tela,5)
map = ss.spritesheet('rpgsprites//Maptl.png',1,1,tela,0)


anim_pers_w = anm.animation((0,0),3,37,2,5)
anim_pers_a = anm.animation((0,0),3,13,2,5)
anim_pers_s = anm.animation((0,0),3,1,2,5)
anim_pers_d = anm.animation((0,0),3,25,2,5)

anm_efect = anm.animation((300,300),61)




end = True
while end:
  
 # ss.draw(map,(0,0),0)
  
  ev.events()
  
  xy = ev.log_events['mouse']
  if xy != None:
      
      mov.set_dir(mov_pers,xy,2)
      if 20 < xy[0] < 120 and 20 < xy[1] < 120:
          end = False
          continue
          
  anm.mod_anim_pos(anim_pers_w,mov.run(mov_pers))
  anm.mod_anim_pos(anim_pers_a,mov.run(mov_pers))
  anm.mod_anim_pos(anim_pers_s,mov.run(mov_pers))
  anm.mod_anim_pos(anim_pers_d,mov.run(mov_pers))
  
  anm.mod_anim_pos(anm_efect,(mov_pers.x-34,mov_pers.y-120))
  
  
  
  if mov_pers.stop == True:
      
      if mov_pers.dir[0] == 'w':
          ss.draw(pers,(mov_pers.x,mov_pers.y),37)
      if mov_pers.dir[0] == 'a':
          ss.draw(pers,(mov_pers.x,mov_pers.y),14)
      if mov_pers.dir[0] == 's':
          ss.draw(pers,(mov_pers.x,mov_pers.y),1)
      if mov_pers.dir[0] == 'd':
          ss.draw(pers,(mov_pers.x,mov_pers.y),25)
      if mov_pers.dir[0] == 'x':
          ss.draw(pers,(mov_pers.x,mov_pers.y),2)
  else:
      if mov_pers.dir[0] == 'w':
          anm.draw_anim(anim_pers_w,pers)
      if mov_pers.dir[0] == 'a':
          anm.draw_anim(anim_pers_a,pers)
      if mov_pers.dir[0] == 's':
          anm.draw_anim(anim_pers_s,pers)
      if mov_pers.dir[0] == 'd':
          anm.draw_anim(anim_pers_d,pers)
      
  anm.draw_anim(anm_efect,efect)
  ss.draw(arm,(mov_pers.x-60,mov_pers.y-45),53)
 
  #mov.debug(tela,mov_pers)
  
  pygame.draw.rect(tela,(200,20,20,90),[20,20,100,100])
  
  
  pygame.display.update()
  
  tela.fill((0,0,0))
 
  #slp(0.016)