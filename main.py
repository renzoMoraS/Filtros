import os
import time
import numpy as np
import matplotlib.pyplot as plt


img_size = [4000,4000,4000,4000]
mt_times = []
st_times = []
for imageIndex in range(0,4):
   
    cmd_multithread  = "tp 1 4 imgs/img" + str(imageIndex)+".ppm"
    cmd_singlethread = "tp 1 1 imgs/img" + str(imageIndex)+".ppm"
    mt_trial_times = []
    st_trial_times = []
    
    for trial in range(0,10):
        
        start = time.time()
        os.system(cmd_multithread)
        finish = time.time()
        mt_trial_times.append((finish-start))
     
        start = time.time()
        os.system(cmd_singlethread)
        finish = time.time()
        st_trial_times.append((finish-start))
    
    mt_times.append(sum(mt_trial_times) / len(mt_trial_times))
    st_times.append(sum(st_trial_times) / len(st_trial_times))

# set width of bar
barWidth = 0.3
 
# set height of bar
bars1 = mt_times
bars2 = st_times

 
# Set position of bar on X axis
r1 = np.arange(len(bars1))
r2 = [x + barWidth for x in r1]
r3 = [x + barWidth for x in r2]
 
# Make the plot
plt.bar(r1, bars1, color='#20b2aa', width=barWidth, edgecolor='white', label='4 threads')
plt.bar(r2, bars2, color='#2e8b57', width=barWidth, edgecolor='white', label='no threads')
plt.gca().set_yscale('log')
# Add xticks on the middle of the group bars
plt.xlabel('imagenes')
plt.ylabel('duración(s)')

plt.xticks([r + barWidth for r in range(len(bars1))], ['img0', 'img1', 'img3', 'img4'])
 
# Create legend & Show graphic
plt.legend()
plt.show()
print(mt_times)