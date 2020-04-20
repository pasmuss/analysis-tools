signalstrengths = ["0p0","0p05","0p1","0p25","0p5","1p0","5p0"]

for strength in signalstrengths:
    print("Starting " + strength)
    instring = "r_" + strength + ".txt"
    outstring = "pulls_" + strength + ".txt"

    combineresults = open(instring,"r")
    individualresults = combineresults.readlines()

    pulls = []
    rexp = float(strength.replace("p","."))

    for oneresult in individualresults:
        words = oneresult.split()
        rvalue = words[3]
        upperuncert = ((words[4].split('/'))[1]).split('+')[1]#uncertainties are given as -x.yz/+a.bc --> first get + part as - can be strongly biased towards negative values --> only get number without + sign
        pull = (float(rvalue)-rexp)/float(upperuncert)
        pulls.append(pull)

    with open (outstring,"w") as output:
        for onepull in pulls:
            if onepull == pulls[-1]:
                output.write(str(onepull))
            else:
                output.write(str(onepull)+"\n")
