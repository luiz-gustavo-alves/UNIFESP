from config.encrypt.SDES import SDESconvert_bin, SDEScripto_block, SDESdescripto_block, SDESconvert_str

init_vector = "10101111"

def xor(a, b):
  res = ""
  for i in range(len(a)):
    if a[i] == b[i]:
      res += "0"
    else:
      res += "1"
  return res

def cbc_cripto(message, key):
  list_bin = SDESconvert_bin(message)
  list_cripto = []
  cipher_block = init_vector
  for i in range(0, len(list_bin)):
    list_bin[i] = xor(list_bin[i], cipher_block)
    list_cripto.append(SDEScripto_block(list_bin[i], key))
    cipher_block = list_cripto[i]
  message_cifra = ''.join(list_cripto)
  return message_cifra

def cbc_descripto(message_cifra, key):
  list_cripto = []
  for i in range(0, len(message_cifra), 8):
    list_cripto.append(message_cifra[i:i + 8])
  list_descripto = []
  cipher_block = init_vector
  for i in range(0, len(list_cripto)):
    list_descripto.append(SDESdescripto_block(list_cripto[i], key))
    list_descripto[i] = xor(list_descripto[i], cipher_block)
    cipher_block = list_cripto[i]
  message = SDESconvert_str(list_descripto)
  return message