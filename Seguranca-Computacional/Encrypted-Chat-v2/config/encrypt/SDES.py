p8_table = [6, 3, 7, 4, 8, 5, 10, 9]
p10_table = [3, 5, 2, 7, 4, 10, 1, 9, 8, 6]
p4_table = [2, 4, 3, 1]
IP = [2, 6, 3, 1, 4, 8, 5, 7]
IP_inv = [4, 1, 3, 5, 7, 2, 8, 6]
expansion = [4, 1, 2, 3, 2, 3, 4, 1]
s0 = [[1, 0, 3, 2], [3, 2, 1, 0], [0, 2, 1, 3], [3, 1, 3, 2]]
s1 = [[0, 1, 2, 3], [2, 0, 1, 3], [3, 0, 1, 0], [2, 1, 0, 3]]


def apply_table(inp, table):
  res = ""
  for i in table:
    res += inp[i - 1]
  return res


def left_shift(data):
  return data[1:] + data[0]


def xor(a, b):
  res = ""
  for i in range(len(a)):
    if a[i] == b[i]:
      res += "0"
    else:
      res += "1"
  return res


def apply_sbox(s, data):
  row = int("0b" + data[0] + data[-1], 2)
  col = int("0b" + data[1:3], 2)
  return bin(s[row][col])[2:]


def function(expansion, s0, s1, key, message):
  left = message[:4]
  right = message[4:]
  temp = apply_table(right, expansion)
  temp = xor(temp, key)
  l = apply_sbox(s0, temp[:4])
  r = apply_sbox(s1, temp[4:])
  l = "0" * (2 - len(l)) + l
  r = "0" * (2 - len(r)) + r
  temp = apply_table(l + r, p4_table)
  temp = xor(left, temp)
  return temp + right


def cripto(text, key1, key2):
  temp = apply_table(text, IP)
  temp = function(expansion, s0, s1, key1, temp)
  temp = temp[4:] + temp[:4]
  temp = function(expansion, s0, s1, key2, temp)
  cifra = apply_table(temp, IP_inv)
  return cifra


def descripto(cifra, key1, key2):
  temp = apply_table(cifra, IP)
  temp = function(expansion, s0, s1, key2, temp)
  temp = temp[4:] + temp[:4]
  temp = function(expansion, s0, s1, key1, temp)
  text = apply_table(temp, IP_inv)
  return text


def SDEScripto_block(text, key):
  temp = apply_table(key, p10_table)
  left = temp[:5]
  right = temp[5:]
  left = left_shift(left)
  right = left_shift(right)
  key1 = apply_table(left + right, p8_table)
  left = left_shift(left)
  right = left_shift(right)
  left = left_shift(left)
  right = left_shift(right)
  key2 = apply_table(left + right, p8_table)
  cifra = cripto(text, key1, key2)
  return cifra


def SDESdescripto_block(cifra, key):
  temp = apply_table(key, p10_table)
  left = temp[:5]
  right = temp[5:]
  left = left_shift(left)
  right = left_shift(right)
  key1 = apply_table(left + right, p8_table)
  left = left_shift(left)
  right = left_shift(right)
  left = left_shift(left)
  right = left_shift(right)
  key2 = apply_table(left + right, p8_table)
  text = descripto(cifra, key1, key2)
  return text


def SDESconvert_bin(message):
  list_bin = []
  for c in message:
    if c < "@" and c >= ' ':
      list_bin.append("00" + format(ord(c), 'b'))
    else:
      list_bin.append("0" + format(ord(c), 'b'))
  return list_bin


def SDESconvert_str(message_bin):
  string = []
  for val in message_bin:
    integer = int(val, 2)
    character = chr(integer)
    string.append(character)
  string = ''.join(string)
  return string


def sdes_cripto(message, key):
  list_bin = SDESconvert_bin(message)
  list_cripto = []
  for i in range(0, len(list_bin)):
    list_cripto.append(SDEScripto_block(list_bin[i], key))
  #print(list_cripto)
  message_cifra = ''.join(list_cripto)
  return message_cifra


def sdes_descripto(message_cifra, key):
  list_cripto = []
  for i in range(0, len(message_cifra), 8):
    list_cripto.append(message_cifra[i:i + 8])
  list_descripto = []
  for i in range(0, len(list_cripto)):
    list_descripto.append(SDESdescripto_block(list_cripto[i], key))
  #print(list_descripto)
  message = SDESconvert_str(list_descripto)
  return message