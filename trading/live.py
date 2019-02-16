import requests
import json
from tabulate import tabulate

URL = "https://www.nseindia.com/live_market/dynaContent/live_watch/stock_watch/%sStockWatch.json"

header = ['Symbol', 'Open', 'High', 'Low', 'LTP', '%30d', '% Change', 'Change', 'Volume', 'Advice?']

broad_indexes = ['nifty', 'juniorNifty', 'niftyMidcap50']

sector_indexes = ['cnxAuto', 'bankNifty',
           'cnxEnergy', 'cnxFinance', 'cnxFMCG', 'cnxit', 'cnxMedia', 'cnxMetal',
           'cnxPharma', 'cnxPSU', 'cnxRealty', 'niftyPvtBank']

def value(string):
    if string == '-':
        string = '0'
    string = string.replace('-', '')
    return float(string.replace(',', ''))

def genKiteOrder(scrip, buyOrSell, price, quantity=10):
    return """
    kite.add({
        "exchange": "NSE",
        "tradingsymbol": "%s",
        "transaction_type": "%s",
        "order_type": "LIMIT",
        "quantity": %d,
        "price": %.2f,
        "product": "MIS"
    });
    """ % (scrip, buyOrSell, quantity, price)

def genWebpage(indexes = broad_indexes):
    data = []
    for index in indexes:
        quotes = getQuotes(index)
        processQuotes(quotes, data)
    template = open('order-tmpl.html', 'r').read()
    orderList = ""
    count = 0
    for order in data:
       ltp = order[4]
       advice = order[-1]
       if order[5] is None or order[4] > 5000:
           continue
       count += 1
       if count > 8: break
       orderList += genKiteOrder(order[0], advice, ltp)
       print order
    f = open('market-order.html', 'w')
    f.write(template.replace('KITEORDERS', orderList))
    f.close()

def getQuotes(index="nifty"):
    response = requests.get(URL % index)
    j = json.loads(response.text)
    return j

def processQuotes(result, data = []):
    quotes = result['data']
    i = result['latestData'][0]
    localData = []
    for q in quotes:
        name = q['symbol']
        o = value(q['open'])
        h = value(q['high'])
        l = value(q['low'])
        wkh = value(q['wkhi'])
        wkl = value(q['wklo'])
        ltp = value(q['ltP'])
        pc = value(q['previousClose'])
        change = q['ptsC']
        monPer = q['mPC']
        per = q['per']
        vol = q['trdVol']
        advice = None
        isBuy = abs(o - l) < 0.1
        isSell = abs(o - h) < 0.1
        if isBuy or isSell:
            if isBuy and h > o and ltp > o:
                advice = "BUY"
            elif isSell and l < o and ltp < h:
                advice = "SELL"
            localData.append([name, o, h, l, ltp, monPer, per, change, vol, advice])
    if len(localData) > 0:
        data.append([i['indexName'], i['open'], i['high'], i['low'], i['ltp'], None, None, i['ch'], None, None])
        localData = sorted(localData, key=lambda x: abs(value(x[7])), reverse=True)
        for s in localData:
            data.append(s)

def display(indexes):
    data = []
    for index in indexes:
        quotes = getQuotes(index)
        processQuotes(quotes, data)
        data.append([None] * len(header))
    print tabulate(data, headers=header)

def display_nifty500():
    display(['nifty500'])

def display_broad():
    display(broad_indexes)

def display_sector():
    display(sector_indexes)
