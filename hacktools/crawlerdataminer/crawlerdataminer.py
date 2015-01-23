# Social Network Profile crawler and data miner
# Author: Rohit Yadav <rohityadav89 AT gmail.com>
# One of my original awesome hacks :) Logins inside a social networking site,
# crawls the profiles based on some rule and saves the pages and logs out.
# Next data miner for some information, exports as a CSV file for using with
# spreadsheet program.

import re, os
import urllib, urllib2, cookielib
from lxml import etree

links = {}

DOMAIN = 'domain.com'
PROFILE_URL = 'http://www.%s/members/' % DOMAIN
LOGIN_URL = 'https://www.%s/Login.aspx?returl=' % DOMAIN
LOGOUT_URL = 'https://www.%s/Logout.aspx' % DOMAIN

def filterProfileLinks(htmlData):
    rawResult = re.findall("""<a href="http://www.domain.com/members/\?id=[0-9]*" id=[A-Za-z0-9_='"(); >.-]*</a>""", htmlData)
    for res in rawResult:
        url = re.findall(PROFILE_URL + """\?id=[0-9]*""", res)
        name = re.findall(""">[A-Za-z0-9_='"();,->. \t]*<""", res)[0][1:-1]
        links[len(links)+1] = {"name" : name, "url" : url[0]}
        
def processSearchResults():
    i = 1
    while i < 27: # No of result pages are 26, you should download the search results pages manually and store in searchpages dir
        filename = "searchpages/%d.html" % i
        f = open(filename , 'r')
        print "[%3d %%] Processing file: %s...\n" % (i*100/26, filename),
        filterProfileLinks(f.read())
        i = i+1
    f = open('profile-links.txt', 'w')
    f.write("%d" % len(links))
    print "\nProcessed total %s search results" % len(links)
    for key in links.keys():
        f.write("\n%s | %s" % (links[key]["url"], links[key]["name"]))
    f.close()

def crawlProfilePages():
    username = ''
    password = ''

    cj = cookielib.CookieJar()
    opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))

    # Login info and protocol is domain specific, so login_data
    login_data = urllib.urlencode({'ERR_u' : 'u|Username|20|1||0', 'ERR_p' : 'p|Password|20|1||0', 'u' : username, 'p' : password})

    print "LET THE HACKING BEGIN!"
    print '[*] Trying to log in...'
    opener.open( LOGIN_URL, login_data)
    print "[+] Logged in! Getting profiles..."

    os.mkdir('profiles')
    i = 1
    for key in links.keys():
        print "Fetching profile of %s from %s" % (links[key]["name"], links[key]["url"])
        resp = opener.open(links[key]["url"])
        output = "profiles/%s.html" % key
        f = open(output, 'w')
        f.write(resp.read())
        f.close()
        print "[%s %%] Saved profile page of %s in file: %s " % (i*100/len(links), links[key]["name"], output)
        i = i + 1

    print "\n[-]Logging out!"
    opener.open( LOGOUT_URL )

def cleanList(info):
    output = []
    for item in info:
        if stripListString(item) != u'[' and stripListString(item) != 'Map' and stripListString(item) != ' ]' and stripListString(item) != '':
            output.append(stripListString(item)+' ')
    return output

def stripListString(string):
    if "<!--" in string: return "" # it's a html comment
    output = ""
    lenght = len(string)
    whitespace, space = False, False
    for char in string:
        if char in ['\r', '\n', '\t', u'\xa0', u'\xbb', ' ']:
            whitespace = True
            if char == ' ': space = True
        else:
            if whitespace == True:
                if space == True: output += ' '
                whitespace, space = False, False
            output += char
    if output == ' ': return ''
    return output.encode('ascii', 'ignore')

def parseProfiles(profileDir):
    for key in range(1, len(links)+1):
        f = open("%s/%d.html" % (profileDir, key), 'r')
        data = f.read()
        f.close()

        parsedPage = etree.HTML(data)
        rawData = parsedPage.xpath("//table[contains(@class, 'ViewTable1')]//text()")
        cleanData = cleanList(rawData)

        for item in cleanData:
            if "Class Year Group:" in item:
                links[key]["year"] = item[len("Class Year Group: "):-1]
        print "[#] Processing for [%3d]: %s, %s" % (key, links[key]["year"], links[key]["name"])

        pindex = cleanData.index("Personal Information ") + 1
        proindex = cleanData.index('Professional Information ') + 1
        addindex = cleanData.index('Additional Information ') + 1

        if 'More Information ' in cleanData:
            moreindex = cleanData.index('More Information ') + 1
            links[key]["moreinfo"] = ''.join(cleanData[moreindex:])
        else:
            moreindex = len(cleanData)
            links[key]["moreinfo"] = ''

        if 'Business Email: ' in cleanData:
            links[key]["email"] = cleanData[cleanData.index('Business Email: ') + 1]
        else:
            links[key]["email"] = ''

        i = pindex
        while i < proindex:
            if ":" in cleanData[i]: break
            i += 1
        links[key]["address"] = ''.join(cleanData[pindex:i])
        links[key]["personalinfo"] = ''.join(cleanData[i:proindex-1])
        links[key]["proinfo"] = ''.join(cleanData[proindex:addindex-1])
        links[key]["addinfo"] = ''.join(cleanData[addindex:moreindex-1])


def outputCSV(filename):
    f = open(filename, 'w')
    # Comma Separated Value file, well ; separated :)
    f.write("Name;Year;Email;Professional Information;Profile Url;Home Address;Personal Information;Additional Information;More Information\n")
    for key in links.keys():
        string = "%s;%s;%s;%s;%s;%s;%s;%s;%s\n" % (links[key]["name"], links[key]["year"], links[key]["email"],
                                             links[key]["proinfo"], links[key]["url"], links[key]["address"], links[key]["personalinfo"],
                                             links[key]["addinfo"], links[key]["moreinfo"])
        f.write(string)
    f.close()

def main():
    profileLinkFile = "profile-links.txt"
    if not os.path.exists(profileLinkFile):
        processSearchResults()
    else:
        global links
        links = {}
        f = open(profileLinkFile, 'r')
        print "[*] Got %s profile links from %s file" % (int(f.readline()), profileLinkFile)
        lines = f.readlines()
        f.close()
        for line in lines:
            data = line.split(" | ")
            links[len(links)+1] = {"name" : data[1][:-1], "url" : data[0]}

    profileDir = "profiles"
    if not os.path.exists(profileDir):
        crawlProfilePages()

    print "[*] Got all the profiles!"
    parseProfiles(profileDir)
    outputCSV("output.csv")

if __name__ == "__main__":
    main()
