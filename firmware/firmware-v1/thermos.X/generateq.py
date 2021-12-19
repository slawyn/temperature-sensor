
def twoscomplement(value, bits):
    if value & (1 << (bits-1)):
        value -= 1 << bits
    return value

def tohex(val, nbits):
  return hex((val + (1 << nbits)) % (1 << nbits))

# -55 .. 70  5 C steps
RtoR25Ratio = [85.423, 60.781, \
               43.65, 31.629, \
               23.118, 17.04, \
               12.649, 9.4864, \
               7.1545, 5.4479, \
               4.1732, 3.2256, \
               2.5147, 1.9763, \
               1.5649, 1.2481, \
               1.0, 0.80956, \
               0.65726, 0.53697, \
               0.44169, 0.36534, \
               0.30327,0.25313, \
               0.21271,0.17962]
R25 = 1000
with open("generateq","w") as f:
    q = 1024
    count = len(RtoR25Ratio)
    f.write("int16_t arri16QTemperatureValues[%d] = {\n"%(count))
    
    Vref = 3.3
    V25 = 3.3*R25/(R25+1000)
    Vadc = 0x0FFF
    TempBase = -55
    for i in range(count):
        Rt = RtoR25Ratio[i] * R25
        Vt = Vref * Rt/(Rt+R25)
        Vx = int((V25-Vt)/Vref * Vadc)
        f.write("%s"%tohex(int(Vx),16))
        if i <count-1:   
            f.write(", // %d\n"%(TempBase+i*5))
        else:
            f.write(" // %d\n};"%(TempBase+i*5))        
    
