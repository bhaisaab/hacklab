import json
import urllib2
import pickle

from BeautifulSoup import BeautifulSoup


def scrapeUrls():
    response = urllib2.urlopen('http://usesthis.com/interviews/')
    data = response.read()
    soup = BeautifulSoup(data)
    links = soup.findAll('a')
    validLinks = []
    for link in links:
        href = link['href']
        if href.startswith('http://') and href.endswith('usesthis.com/'):
            validLinks.append(href)
    return validLinks


def scrapeInterview(link):
    response = urllib2.urlopen(link + "/json")
    data = response.read()
    interview = {}
    try:
        interview = json.loads(data)
    except Exception: # gotta catch 'em all
        pass
    return interview


def main():
    print 'Scraping usesthis.com'
    interviews = []
    links = scrapeUrls()
    for index, link in enumerate(links):
        print '%3d/%3d %s' % (index + 1, len(links), link)
        interview = scrapeInterview(link)
        model = {'name': interview['name'],
                 'categories': interview['categories'],
                 'wares': interview['wares']}
        interviews.append(model)
    pickle.dump(interviews, open('usesthis.pickle', 'wb'))


if __name__ == '__main__':
    main()
