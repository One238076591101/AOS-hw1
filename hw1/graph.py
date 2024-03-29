import matplotlib.pyplot as plt

# 第一種測試字串Random String程式數據結果放入list中
num_frames = [20, 40, 60, 80, 100]
fifo_page_faults = [197134,193120 , 189015, 184888, 181025]
arb_page_faults = [195865, 191893, 187895, 183836, 179842]
esc_page_faults = [196056, 192166, 188026, 183963, 180354]
lrud_page_faults = [197108, 193161, 189041, 184852, 180686]

fifo_interrupts = [18118, 17776, 17387, 17006, 16663]
arb_interrupts = [22119, 25529, 29527, 33378, 37164]
esc_interrupts = [8572, 12324, 16386, 20330, 23893]
lrud_interrupts = [18136, 17817, 17429, 17050, 16681]

fifo_disk_writes = [18118, 17776, 17387, 17006, 16663]
arb_disk_writes = [17984, 17422, 17422, 17214, 17006]
esc_disk_writes = [4628, 4490, 4412, 4293, 4247]
lrud_disk_writes = [18136, 17817, 17429, 17050, 16681]

# 建立三個水平子圖
fig, axs = plt.subplots(1, 3, figsize=(15, 5))

# 設定圖表標題
fig.suptitle("Algorithm Performance vs. Number of Frames")

# 繪製第一張圖：Page Faults vs. Number of Frames
axs[0].plot(num_frames, fifo_page_faults, label="FIFO", marker='o')
axs[0].plot(num_frames, arb_page_faults, label="ARB", marker='s')
axs[0].plot(num_frames, esc_page_faults, label="ESC", marker='^')
axs[0].plot(num_frames, lrud_page_faults, label="LRUD", marker='D')  
axs[0].set_title("Random String -four algorithm performance")
axs[0].set_xlabel("Number of Frames")
axs[0].set_ylabel("Page Faults")
axs[0].legend()

# 繪製第二張圖：Interrupts vs. Number of Frames
axs[1].plot(num_frames, fifo_interrupts, label="FIFO", marker='o')
axs[1].plot(num_frames, arb_interrupts, label="ARB", marker='s')
axs[1].plot(num_frames, esc_interrupts, label="ESC", marker='^')
axs[1].plot(num_frames, lrud_interrupts, label="LRUD", marker='D') 
axs[1].set_title("Random String -four algorithm performance")
axs[1].set_xlabel("Number of Frames")
axs[1].set_ylabel("Interrupts")
axs[1].legend()

# 繪製第三張圖：Disk Writes vs. Number of Frames
axs[2].plot(num_frames, fifo_disk_writes, label="FIFO", marker='o')
axs[2].plot(num_frames, arb_disk_writes, label="ARB", marker='s')
axs[2].plot(num_frames, esc_disk_writes, label="ESC", marker='^')
axs[2].plot(num_frames, lrud_disk_writes, label="LRUD", marker='D') 
axs[2].set_title("Random String -four algorithm performance")
axs[2].set_xlabel("Number of Frames")
axs[2].set_ylabel("Disk Writes")
axs[2].legend()

# 調整子圖之間的間距
plt.tight_layout()

# 顯示圖表
plt.show()
