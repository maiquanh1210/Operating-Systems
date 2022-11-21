import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

def read_txt(path):
    with open(path) as f:
        data = f.readlines()
    data_ = []
    for i, val in enumerate(data[:-1]):
        val=val.replace(',', '.')
        data_.append([float(j) for j in val[:-1].split()])

    data_ = np.asarray(data_)
    class_ = np.unique(data_[:,0])

    dict_ = {}
    for id, val in enumerate(class_):
        data_pid = [j for j in data_[:-1] if (j[0]==val)]
        dict_[id] = data_pid

    num_proc = len(class_)

    time = [float(j)/1000000 for j in data[-1].split()]
    return data_, dict_, time, num_proc
config=[]

def get_mean(dict_val):
    raw = [i[1] for i in dict_val]
    cpu = [i[-1] for i in dict_val]
    mean_raw = sum(raw)/len(dict_val)
    mean_cpu = sum(cpu)/len(dict_val)
    return mean_raw, mean_cpu
def plot_img(dict_val, time, num_process):
    mean_raw_list = []
    mean_cpu_list = []
    for id in range(num_process):
        fig, axs = plt.subplots(2)
        x = [i for i in range(len(dict_val[id]))]
        raw = [i[1] for i in dict_val[id]]
        cpu = [i[-1] for i in dict_val[id]]
        mean_raw, mean_cpu = get_mean(dict_val[id])
        mean_raw_list.append(mean_raw)
        mean_cpu_list.append(mean_cpu)
        
        plt.suptitle("{}th: RAM: {:.2f} KB | CPU(%): {:.4f} | Time: {:.4f}(ms)".format(id+1,mean_raw, mean_cpu, time[id]))
        axs[0].plot(x, raw, color='g')
        axs[1].plot(x, cpu)
        axs[0].set_xlabel('timestamp')
        axs[0].set_ylabel('RAM (KB)')
        axs[1].set_xlabel('timestamp')
        axs[1].set_ylabel('CPU(%)')
        axs[0].grid()
        axs[1].grid()
        path = "process{}.png".format(id+1)
        plt.savefig(path)
        
    
def main():
    config=[]
    data_, dict_val, time, num_proc=read_txt("/home/quanh/Documents/quanh/process_syn/data.txt")
    # plot_img(dict_val, time, num_proc)    
    for i in range(num_proc):
        mean_raw, mean_cpu = get_mean(dict_val[i])
        config.append([mean_raw, mean_cpu, 0])
    config.append([sum(data_[:,1])/data_.shape[0], sum(data_[:,-1])/data_.shape[0],sum(time)/len(time)])
    config = pd.DataFrame(config, columns =['RAM','CPU','Time'])
    config.to_csv('results.csv', index=False)

main()




    


