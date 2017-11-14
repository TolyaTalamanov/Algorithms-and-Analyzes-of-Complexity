from subprocess import Popen, PIPE

def one_experiment(N):
    exe = "../cmake-build-debug/Sorts "
    comand = exe + str(N) +" " + str(1)
    proc = Popen(comand, shell=True, stdout=PIPE, stderr=PIPE)
    proc.wait()    
    res = proc.communicate()  
    if proc.returncode:
       return res[1]
    return res[0]

def serial_experiment(N, count):
    avg_time = 0
    
    for i in range(count):
      time = float(one_experiment(N))
      avg_time += time

    avg_time /= count
    return avg_time

def write_log(step):
    lower_bound = 1
    upper_bound = 1000000
    i = lower_bound
    f = open('log.txt', 'w')
    while(i <= upper_bound):
        avg_time = float(serial_experiment(i, 10))
        f.write(str(avg_time) + "\n")
        i *= step
        
 
    f.close()    

write_log(10)

    
	



