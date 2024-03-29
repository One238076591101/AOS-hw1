import matplotlib.pyplot as plt

# 第二種測試字串Locality String程式數據結果放入list中
num_frames = [20, 40, 60, 80, 100]
fifo_page_faults = [126424,113228 , 110933, 108796, 106372]
arb_page_faults = [191342, 187199, 183266, 179332, 175441]
esc_page_faults = [191554, 187660, 183588, 179192, 174897]
lrud_page_faults = [126312, 112979, 110696, 108431, 106026]

fifo_interrupts = [12323, 10993, 10783, 10582, 10375]
arb_interrupts = [26999, 30919, 34076, 37629, 41508]
esc_interrupts = [13389, 17090, 21022, 25365, 29410]
lrud_interrupts = [12318, 10980, 10774, 10562, 10342]

fifo_disk_writes = [12323, 10993, 10783, 10582, 10375]
arb_disk_writes = [18341, 18118, 17342, 16961, 16949]
esc_disk_writes = [4943, 4750, 4610, 4557, 4307]
lrud_disk_writes = [12318, 10980, 10774, 10562, 10342]

# 建立三個水平子圖
fig, axs = plt.subplots(1, 3, figsize=(15, 5))

# 設定圖表標題
fig.suptitle("Algorithm Performance vs. Number of Frames")

# 繪製第一張圖：Page Faults vs. Number of Frames
axs[0].plot(num_frames, fifo_page_faults, label="FIFO", marker='o')
axs[0].plot(num_frames, arb_page_faults, label="ARB", marker='s')
axs[0].plot(num_frames, esc_page_faults, label="ESC", marker='^')
axs[0].plot(num_frames, lrud_page_faults, label="LRUD", marker='D')  
axs[0].set_title("Locality String -four algorithm performance")
axs[0].set_xlabel("Number of Frames")
axs[0].set_ylabel("Page Faults")
axs[0].legend()

# 繪製第二張圖：Interrupts vs. Number of Frames
axs[1].plot(num_frames, fifo_interrupts, label="FIFO", marker='o')
axs[1].plot(num_frames, arb_interrupts, label="ARB", marker='s')
axs[1].plot(num_frames, esc_interrupts, label="ESC", marker='^')
axs[1].plot(num_frames, lrud_interrupts, label="LRUD", marker='D') 
axs[1].set_title("Locality String -four algorithm performance")
axs[1].set_xlabel("Number of Frames")
axs[1].set_ylabel("Interrupts")
axs[1].legend()

# 繪製第三張圖：Disk Writes vs. Number of Frames
axs[2].plot(num_frames, fifo_disk_writes, label="FIFO", marker='o')
axs[2].plot(num_frames, arb_disk_writes, label="ARB", marker='s')
axs[2].plot(num_frames, esc_disk_writes, label="ESC", marker='^')
axs[2].plot(num_frames, lrud_disk_writes, label="LRUD", marker='D') 
axs[2].set_title("Locality String -four algorithm performance")
axs[2].set_xlabel("Number of Frames")
axs[2].set_ylabel("Disk Writes")
axs[2].legend()

# 調整子圖之間的間距
plt.tight_layout()

# 顯示圖表
plt.show()
