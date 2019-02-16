from tabulate import tabulate
from nsetools import Nse
import requests
import multiprocessing

nse = Nse()


def allStocks():
    return nse.get_stock_codes()

def allNiftyIndex():
    return nse.get_index_list()

def nifty500():
    stocks = []
    r = requests.get('https://www.nseindia.com/content/indices/ind_nifty500list.csv')
    for c in r.text.split('\n')[:-1]:
        q = c.split(',')
        if q[3] == 'EQ':
            stocks.append(str(q[2]))
    return stocks

stocks = nifty500()

def findBuyP():
    headers = ['Name', 'Open', 'Low', 'High', 'Close', 'Previous Close', 'Recommendation']
    data = []

    def getQuote(stock):
        print 'geting', stock
        try:
            q = nse.get_quote(stock)
            return q
        except: pass
        return None

    pool = multiprocessing.Pool(processes=5)
    pool_outputs = pool.map(getQuote, stocks)
    pool.close()
    pool.join()
    print pool_outputs
    return

    threads = [threading.Thread(target=getQuote, args=(stock,)) for stock in stocks]
    for thread in threads:
        thread.start()
    for thread in threads:
        thread.join()

    for quote in quotes:
        name = quote['companyName']
        openPrice = quote['open']
        closePrice = quote['closePrice']
        previousClose = quote['previousClose']
        high = quote['dayHigh']
        low = quote['dayLow']
        if openPrice == low or openPrice == high:
            suggest = None
            if openPrice == low and high > openPrice:
                suggest = "BUY"
            elif openPrice == high and low < openPrice:
                suggest = "SELL"
            data.append([stock, openPrice, low, high, closePrice, previousClose, suggest])
    return data, headers

data, headers = findBuyP()
print tabulate(data, headers=headers)
