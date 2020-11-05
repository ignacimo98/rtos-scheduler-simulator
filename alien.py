class Alien:
  def __init__(self, id, creacion, periodo, energia, r, g, b):
    self.id = id
    self.creacion = creacion
    self.energia = energia
    self.periodo = periodo
    self.r = r
    self.g = g
    self.b = b

  def recent_deadline(self, time):
    if time>=self.creacion and (time - self.creacion)%self.periodo<self.energia:
      return True
    return False