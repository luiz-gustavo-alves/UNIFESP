from config.encrypt.SDES import sdes_cripto, sdes_descripto

def ecb_cripto(message, key):
    return sdes_cripto(message, key)

def ecb_descripto(message, key):
    return sdes_descripto(message, key)