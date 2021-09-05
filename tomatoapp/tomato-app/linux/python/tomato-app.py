import ctypes  
so = ctypes.cdll.LoadLibrary   
lib = so("/usr/local/lib/libtomatosdk.so")   
print 'Init()'  
lib.RobotInit()  
print 'Start()'  
lib.RobotClose() 
