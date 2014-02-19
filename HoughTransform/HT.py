from ROOT import * 
import numpy as np
from array import array

'gROOT.ProcessLine(".x Documents/PhD_thesis/tmp/rootPlotFiles/lhcbstyle.C")

def view(x,y,lines):
    c3 = TCanvas("c3","c3")
    hPs = TGraph(len(x),array('d',x),array('d',y))
    hPs.Draw("A*")
    hPs.GetXaxis().SetTitle("x")
    hPs.GetYaxis().SetTitle("y")
    for line in lines:
        print line
        line.Draw("same")
        #assert(False)
    return {'lines':lines, 'canvas':c3, 'graph':hPs}

def findLines(myMax,mx,Mx):
    lines = []

    for (index,m) in enumerate(myMax):
        lines.append(TF1("line%s"%index,"([0]-cos([1])*x)/sin([1])",mx,Mx))
        R = m[1]
        Theta = m[0]
        lines[-1].SetParameter(0,R)
        lines[-1].SetParameter(1,Theta)
        #lines[-1].Draw()
    return lines

def makeCluster(max,resX,resY):
    loopList = max[1:]
    a = max[0][0]
    b = max[0][1]
    M = []
    for el in loopList:
        c = el[0]
        d = el[1]
        if fabs(a-c)<=resX and fabs(b-d)<=resY:
            a = (a+c)/2.
            b = (b+d)/2.
        else:
            M.append([a,b])
            a = c
            b = d
    M.append([a,b])
    print "clean max position (bin numbers):",M
    return M

def convertBinVal(h,cleanMaxBins):
    M = []
    for el in cleanMaxBins:
        R = h.GetYaxis().GetBinCenter(int("%.0f"%el[1]))
        Theta = h.GetXaxis().GetBinCenter(int("%.0f"%el[0]))
        M.append([Theta,R])
    return M

def makeLinearHT(x,y,thr,nTheta=100,nRho=100,resX=2,resY=2):
    mx = min(x)
    Mx = max(x)
    my = min(y)
    My = min(y)
    
    ## Prepare the rho/theta space (Hough space)
    step = TMath.Pi()/nTheta
    thetas = []
    tmp = 0.
    for aa in xrange(nTheta):
        tmp += step
        thetas.append(tmp)

    ## Prepare the accumulator matrix: matrix with intersection of lines
    ## First is number of colums (nRho) second is number of row(nTheta)
    #accumulator = np.matrix([[0 for i in xrange(nRho)] for j in xrange(nTheta)])

    mtheta = 0
    Mtheta = TMath.Pi()
    mrho = -10
    Mrho = 10
    h = TH2F("h","h",nTheta,mtheta,Mtheta,nRho,mrho,Mrho)

    ## Convert heach point in the x-y space into a sinusoid function in the Hough space
    c = TCanvas("c","c")
    sinu = []
    
    for i in xrange(len(x)):
        sinu.append(TF1('sinu%s'%i,"[0]*cos(x)+[1]*sin(x)",0,TMath.Pi()))
        print x[i],y[i]
    
        sinu[-1].SetParameter(0,x[i])
        sinu[-1].SetParameter(1,y[i])
        if i==0:
            sinu[-1].GetXaxis().SetTitle("#theta")
            sinu[-1].GetYaxis().SetTitle("#rho")
            sinu[-1].Draw()
        else:
            sinu[-1].Draw("same")

        ## Increment the matrix element correspondent to the intersection of the lines
        for t in thetas:
            r = x[i]*cos(t)+y[i]*sin(t)
            print t,r
            h.Fill(t,r)
            ## the matrix insert definition is opposite respect to the histo one. 
            #accumulator[ir,it]+=1
    preliminaryMax = []
    for i in xrange(nTheta):
        for j in xrange(nRho):
            tmp = h.GetBinContent(i,j)
            if tmp>=thr:
                preliminaryMax.append([i,j, tmp])

    print preliminaryMax
    c2 = TCanvas("c2","c2")
    h.GetXaxis().SetTitle("#theta")
    h.GetYaxis().SetTitle("#rho")
    h.Draw("colz")
    
    cleanMaxBins = makeCluster(preliminaryMax,resX,resY)
    cleanMax = convertBinVal(h,cleanMaxBins)
    lines = findLines(cleanMax,mx,Mx)
    res = view(x,y,lines)
    
    return [c2,h,lines,res]
    #print accumulator
    #assert(False)

x = [4.0,3.2,1.8,1.0,1.0,2.0,3.0]#[1.0, 1.8, 3.2, 4.0]
y = [4.0,3.2,1.8,1.0,3.5,2.5,1.5]#[1.0, 2.1, 2.8, 3.9]


### add noise
nX = [1.0,4.0,2.7]
nY = [5.0,1.2,4.1]

x+=nX
y+=nY
#x = [1.0, 1.8, 3.2, 4.0]
#y = [1.0, 2.1, 2.8, 3.9]


nTheta = 1000
nRho = 1000
thr = 3
resX = 2#30
resY = 2#30

'''c0 = TCanvas("c0","c0")
hPs = TGraph(len(x),array('d',x),array('d',y))
hPs.Draw("A*")
hPs.GetXaxis().SetTitle("x")
hPs.GetYaxis().SetTitle("y")
'''

res = makeLinearHT(x,y,thr,nTheta,nRho,resX,resY)
res[3]['canvas'].Update()


'''
    if i==0:
        sinu[-1].Draw()
    else:
        sinu[-1].Draw("same")


        
from array import array
binx = array('i',[0])
biny = array('i',[0])
binz = array('i',[0])
globBin = h.GetMaximumBin()
h.GetBinXYZ(globBin,binx,biny,binz)
print binx[0],biny[0]
R = h.GetYaxis().GetBinCenter(biny[0])
Theta = h.GetXaxis().GetBinCenter(binx[0])
c2 = TCanvas("c2","c2")
h.Draw("colz")

c3 = TCanvas("c3","c3")
hPs = TGraph(len(x),array('d',x),array('d',y))
hPs.Draw("A*")

line = TF1("line","([0]-cos([1])*x)/sin([1])",0,5)
line.SetParameter(0,R)
line.SetParameter(1,Theta)
line.Draw("same")

assert(False)

r = {}
for i in theta:
    r[i]=[]
for j in xrange(len(x)):
    for t in theta:
        r[t].append(x[j] * cos(t) + y[j] * sin(t))
print theta
print r
h = TH2F("h","h",5,0,6,9,0,TMath.Pi())
for i in xrange(len(x)):
    for t in theta:
        h.Fill(r[t][j],t)
h.Draw("colz")
assert(False)

    
x = [4.0,3.2,1.8,1.0]#[1.0, 1.8, 3.2, 4.0]
y = [3.9,2.8,2.1,1.0]#[1.0, 2.1, 2.8, 3.9]

nTheta = 1000
nR = 1000

x = [4.0,3.2,1.8,1.0,1.0,2.0,3.0]#[1.0, 1.8, 3.2, 4.0]
y = [4.0,3.2,1.8,1.0,3.5,2.5,1.5]#[1.0, 2.1, 2.8, 3.9]

h = TH2F("h2","h2",nTheta,0,TMath.Pi(),nR,-6,6)

for i in xrange(nTheta):
    for j in xrange(nR):
        h.SetBinContent(i,j,0)

c = TCanvas("c","c")
sinu = []

for i in xrange(len(x)):
    sinu.append(TF1('sinu%s'%i,"[0]*cos(x)+[1]*sin(x)",0,TMath.Pi()))
    print x[i],y[i]
    
    sinu[-1].SetParameter(0,x[i])
    sinu[-1].SetParameter(1,y[i])

    for bj in t:
        r = x[i]*cos(bj)+y[i]*sin(bj)
        print bj,r
        h.Fill(bj,r)
    
    
    if i==0:
        sinu[-1].Draw()
    else:
        sinu[-1].Draw("same")


        
from array import array
binx = array('i',[0])
biny = array('i',[0])
binz = array('i',[0])
globBin = h.GetMaximumBin()
h.GetBinXYZ(globBin,binx,biny,binz)
print binx[0],biny[0]
R = h.GetYaxis().GetBinCenter(biny[0])
Theta = h.GetXaxis().GetBinCenter(binx[0])
c2 = TCanvas("c2","c2")
h.Draw("colz")

c3 = TCanvas("c3","c3")
hPs = TGraph(len(x),array('d',x),array('d',y))
hPs.Draw("A*")

line = TF1("line","([0]-cos([1])*x)/sin([1])",0,5)
line.SetParameter(0,R)
line.SetParameter(1,Theta)
line.Draw("same")

assert(False)

r = {}
for i in theta:
    r[i]=[]
for j in xrange(len(x)):
    for t in theta:
        r[t].append(x[j] * cos(t) + y[j] * sin(t))
print theta
print r
h = TH2F("h","h",5,0,6,9,0,TMath.Pi())
for i in xrange(len(x)):
    for t in theta:
        h.Fill(r[t][j],t)
h.Draw("colz")
assert(False)
'''
