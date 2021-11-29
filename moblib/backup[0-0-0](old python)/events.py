
import pygame

log_events = {'mouse':None,'keystate':False}

def events():

    for ev in pygame.event.get():
      if ev.type == pygame.MOUSEMOTION:
          log_events.update({'mouse':pygame.mouse.get_pos()})
      
      if ev.type == pygame.KEYDOWN:
          log_events.update({'keystate':True})
      if ev.type == pygame.KEYUP:
          log_events.update({'keystate':False})