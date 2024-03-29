import matplotlib.pyplot as plt

# 第三種測試字串Custom String程式數據結果放入list中
num_frames = [20, 40, 60, 80, 100]
fifo_page_faults = [197938,195852 , 193795, 191731, 189765]
arb_page_faults = [195987 , 192072, 188066, 184049, 179981]
esc_page_faults = [196113, 192203, 188107, 184122, 180068]
lrud_page_faults = [197928, 195852, 193777, 191721, 189735]

fifo_interrupts = [22914, 22675, 22417, 22176, 21933]
arb_interrupts = [26535, 29459, 33083, 36673, 40341]
esc_interrupts = [9456, 13295, 17302, 21064, 25018]
lrud_interrupts = [22941, 22700, 22461, 22230, 21993]

fifo_disk_writes = [22914, 22675, 22417, 22176, 21933]
arb_disk_writes = [22522, 21531, 21149, 20722, 20322]
esc_disk_writes = [5569, 5498, 5409, 5186, 5086]
lrud_disk_writes = [22941, 22700, 22461, 22230, 21993]

# 建立三個水平子圖
fig, axs = plt.subplots(1, 3, figsize=(15, 5))

# 設定圖表標題
fig.suptitle("Algorithm Performance vs. Number of Frames")

# 繪製第一張圖：Page Faults vs. Number of Frames
axs[0].plot(num_frames, fifo_page_faults, label="FIFO", marker='o')
axs[0].plot(num_frames, arb_page_faults, label="ARB", marker='s')
axs[0].plot(num_frames, esc_page_faults, label="ESC", marker='^')
axs[0].plot(num_frames, lrud_page_faults, label="LRUD", marker='D')  
axs[0].set_title("Custom String -four algorithm performance")
axs[0].set_xlabel("Number of Frames")
axs[0].set_ylabel("Page Faults")
axs[0].legend()

# 繪製第二張圖：Interrupts vs. Number of Frames
axs[1].plot(num_frames, fifo_interrupts, label="FIFO", marker='o')
axs[1].plot(num_frames, arb_interrupts, label="ARB", marker='s')
axs[1].plot(num_frames, esc_interrupts, label="ESC", marker='^')
axs[1].plot(num_frames, lrud_interrupts, label="LRUD", marker='D') 
axs[1].set_title("Custom String -four algorithm performance")
axs[1].set_xlabel("Number of Frames")
axs[1].set_ylabel("Interrupts")
axs[1].legend()

# 繪製第三張圖：Disk Writes vs. Number of Frames
axs[2].plot(num_frames, fifo_disk_writes, label="FIFO", marker='o')
axs[2].plot(num_frames, arb_disk_writes, label="ARB", marker='s')
axs[2].plot(num_frames, esc_disk_writes, label="ESC", marker='^')
axs[2].plot(num_frames, lrud_disk_writes, label="LRUD", marker='D') 
axs[2].set_title("Custom String -four algorithm performance")
axs[2].set_xlabel("Number of Frames")
axs[2].set_ylabel("Disk Writes")
axs[2].legend()

# 調整子圖之間的間距
plt.tight_layout()

# 顯示圖表
plt.show()
