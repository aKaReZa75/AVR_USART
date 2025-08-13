# USART (Universal Synchronous and Asynchronous serial Receiver and Transmitter)

The USART (Universal Synchronous and Asynchronous serial Receiver and Transmitter) is a crucial peripheral in the ATmega328 microcontroller, used for serial communication. It supports both asynchronous and synchronous communication modes. This allows the microcontroller to communicate with other devices (such as sensors, computers, or other microcontrollers) via UART or SPI, depending on the configuration.

<table>
  <tr>
  <td valign="top">
  
  > [!TIP]  
  > If you're looking to better understand how to navigate and use my GitHub repositories — including exploring their structure, downloading or cloning projects, submitting issues, and asking questions,  
  > everything you need is clearly explained in this video:  
  > [aKaReZa 95 - Programming, Git - PART B](https://youtu.be/zYiUItVFRqQ)  
  > Make sure to check it out!
  
  </td>
    <td width="360" valign="middle" style="padding: 0;">
      <a href="https://youtu.be/zYiUItVFRqQ">
       <img src="https://img.youtube.com/vi/zYiUItVFRqQ/maxresdefault.jpg"
             width="360"
             alt="aKaReZa 95 - Programming, Git - PART B Thumbnail"/>
      </a>
    </td>

  </td>
  </tr>
  <tr>
  <td colspan="2">

  > [!CAUTION]
  > It is absolutely critical that you carefully read every single word of this document, line by line, to ensure you don't miss any details. Nothing can be overlooked.
      
  </td>
  </tr>  
</table>

# 🔗 Resources
  Here you'll find a collection of useful links and videos related to the topic of AVR microcontrollers.  

## **USART0 Overview**
```
USART0 Overview
├── Documentation
│   ├─ [USART0 Modes]
│   │   ├─ Registers — UCSR0C (UMSEL0 bits)
│   │   ├─ Modes — Asynchronous, Synchronous
│   │   └─ Examples — Switching modes and timing differences
│   │
│   ├─ [USART0 Baud Rate]
│   │   ├─ Registers — UBRR0H, UBRR0L
│   │   ├─ Concept — Baud rate calculation formula
│   │   └─ Effects — Impact on transmission speed and error rate
│   │
│   ├─ [USART0 Interrupts]
│   │   ├─ Registers — UCSR0B (RXCIE0, TXCIE0, UDRIE0), UCSR0A flags
│   │   ├─ Sources — RX Complete, TX Complete, Data Register Empty
│   │   └─ Control — Enable, flag handling, and ISR examples
│   │
│   ├─ [USART0 Data Registers]
│   │   ├─ UDR0 — USART Data Register (Read/Write)
│   │   ├─ Transmission — Data load and send
│   │   └─ Reception — Data read and buffering
│   │
│   └─ [USART0 Error Handling]
│       ├─ Registers — UCSR0A (FE0, DOR0, UPE0)
│       ├─ Errors — Frame Error, Data Overrun, Parity Error
│       └─ Handling — Error detection and safe recovery
|
├── [API_Reference]
│    ├─ File — usart.h / usart.c
│    ├─ Functions — Init, Write, Puts, getChar, Flush
│    └─ Purpose — High-level USART communication interface
│
└── Registers
    ├─ [UCSR0A] — Status flags: Transmission/Reception status & error flags
    ├─ [UCSR0B] — Control bits: Enable TX/RX, interrupts, and frame size (part 1)
    ├─ [UCSR0C] — Control bits: Mode select, parity, stop bits, data bits (part 2)
    ├─ [UBRR0H] — Baud rate register (high byte)
    ├─ [UBRR0L] — Baud rate register (low byte)
    └─ [UDR0]   — Data register — Holds incoming or outgoing data
```

- [USART0 Modes](./USART0_Modes.md)
  ---
  This document provides a detailed explanation of all operating modes for USART0, including Asynchronous, Synchronous modes, along with the register configurations required and timing implications for each.

- [USART0 Baud Rate](./USART0_BaudRate.md)
  ---
  This file describes how to set the baud rate for USART0 using UBRR0 register, including the baud rate calculation formula, example configurations for common baud rates, and the effect of clock frequency and U2X0 bit on accuracy.

- [USART0 Interrupts](./USART0_Interrupts.md)
  ---
  Covers all USART0 interrupt sources: Receive Complete, Transmit Complete, and Data Register Empty. Explains how to enable them using UCSR0B, read the related flags in UCSR0A, and properly write interrupt service routines (ISR) for each case.

- [USART0 Data Registers](./USART0_DataRegisters.md)
  ---
  Detailed description of UDR0 operation, including how data is buffered for transmission and reception, timing considerations, and tips for avoiding data loss.

- [USART0 Error Handling](./USART0_ErrorHandling.md)
  ---
  This file explains USART0 error flags in UCSR0A (Frame Error, Data Overrun, and Parity Error), how to detect them, and strategies for robust recovery in high-reliability systems.

- [API Reference](./API_Reference.md)
  ---
  This section provides a detailed description of the functions in the `usart.h` and `usart.c` files for handling USART communication on the ATmega328 microcontroller. Each function is designed to manage data transmission and reception through USART, as well as configure the necessary registers.


## **Videos Overview**
```plaintext
AVR, Communication, USART
   ├── [aKaReZa 66 - AVR, Communication, USART - Part A]
   │   ├─ Basics — Features, block diagram, registers.
   │   ├─ BaudRate — Calculation and setup.
   │   ├─ Data Tx — Sending characters and strings.
   │   ├─ Formatting — Escape sequences and frame structure.
   │   └─ Simulation — Software vs hardware testing.
   │
   └── [aKaReZa 67 - AVR, Communication, USART - Part B]
       ├─ Data Rx — Receiving bytes and using interrupts.
       ├─ Reliability — Baud errors, flags, circular buffer.
       ├─ Speed — Double Speed mode usage.
       ├─ Debugging — Data plotting and USART insights.
       └─ Comparison — Simulation vs real-world behavior.
```

<table style="border-collapse: collapse;">
  <tr>
    <td valign="top" style="padding: 0 10px;">
      <h3 style="margin: 0;">
        <a href="https://youtu.be/TJEfbymLoTs">aKaReZa 66 – AVR, Communication, USART - Part A</a>
      </h3>
      <p style="margin: 8px 0 0;">
        Learn about USART features and specifications in the ATMega328 microcontroller, including baud rate calculation, registers, single character and string transmission, escape sequences, data frames, and differences in simulation and practical testing.
      </p>
    </td>
    <td width="360" valign="top" style="padding: 0;">
      <a href="https://youtu.be/TJEfbymLoTs">
        <img src="https://img.youtube.com/vi/TJEfbymLoTs/maxresdefault.jpg"
             width="360"
             alt="aKaReZa 66 – AVR, Communication, USART - Part A Thumbnail"/>
      </a>
    </td>
  </tr>

  <tr>
    <td valign="top" style="padding: 0 10px;">
      <h3 style="margin: 0;">
        <a href="https://youtu.be/HWJqS9NjYIA">aKaReZa 67 – AVR, Communication, USART - Part B</a>
      </h3>
      <p style="margin: 8px 0 0;">
        Continuation of USART communication, discussing escape sequences, byte reception, baud rate errors and solutions, double speed mode, data reception with interrupts, circular buffer, USART flags, debugging, and data frames.
      </p>
    </td>
    <td width="360" valign="top" style="padding: 0;">
      <a href="https://youtu.be/HWJqS9NjYIA">
        <img src="https://img.youtube.com/vi/HWJqS9NjYIA/maxresdefault.jpg"
             width="360"
             alt="aKaReZa 67 – AVR, Communication, USART - Part B Thumbnail"/>
      </a>
    </td>
  </tr>
</table>
  
> [!TIP]
> The resources are detailed in the sections below.  
> To access any of them, simply click on the corresponding blue link.

- [AVR Microntroller](https://github.com/aKaReZa75/AVR)
  ---  
    This repository contains comprehensive resources for AVR microcontrollers, including hardware schematics, software libraries, and educational projects.

# 💻 How to Use Git and GitHub
To access the repository files and save them on your computer, there are two methods available:
1. **Using Git Bash and Cloning the Repository**
   - This method is more suitable for advanced users and those familiar with command-line tools.
   - By using this method, you can easily receive updates for the repository.

2. **Downloading the Repository as a ZIP file**
   - This method is simpler and suitable for users who are not comfortable with command-line tools.
   - Note that with this method, you will not automatically receive updates for the repository and will need to manually download any new updates.

## Clone using the URL.
First, open **Git Bash** :
-  Open the folder in **File Explorer** where you want the library to be stored.
-  **Right-click** inside the folder and select the option **"Open Git Bash here"** to open **Git Bash** in that directory.

![open Git Bash](Images/Step0.png)

> [!NOTE] 
> If you do not see the "Open Git Bash here" option, it means that Git is not installed on your system.  
> You can download and install Git from [this link](https://git-scm.com/downloads).  
> For a tutorial on how to install and use Git, check out [this video](https://youtu.be/BsykgHpmUt8).
  
-  Once **Git Bash** is open, run the following command to clone the repository:

 ```bash
git clone https://github.com/aKaReZa75/AVR_USART.git
```
- You can copy the above command by either:
- Clicking on the **Copy** button on the right of the command.
- Or select the command text manually and press **Ctrl + C** to copy.
- To paste the command into your **Git Bash** terminal, use **Shift + Insert**.

![Clone the Repository](Images/Step1.png)

- Then, press Enter to start the cloning operation and wait for the success message to appear.

![Open the Library File](Images/Step2.png)

> [!IMPORTANT]
> Please keep in mind that the numbers displayed in the image might vary when you perform the same actions.  
> This is because repositories are continuously being updated and expanded. Nevertheless, the overall process remains unchanged.

> [!NOTE]
> Advantage of Cloning the Repository:  
> - **Receiving Updates:** By cloning the repository, you can easily and automatically receive new updates.  
> - **Version Control:** Using Git allows you to track changes and revert to previous versions.  
> - **Team Collaboration:** If you are working on a project with a team, you can easily sync changes from team members and collaborate more efficiently.  

## Download Zip
If you prefer not to use Git Bash or the command line, you can download the repository directly from GitHub as a ZIP file.  
Follow these steps:  
1. Navigate to the GitHub repository page and Locate the Code button:
   - On the main page of the repository, you will see a green Code button near the top right corner.

2. Download the repository:
   - Click the Code button to open a dropdown menu.
   - Select Download ZIP from the menu.

  ![Download Zip](Images/Step7.png)  

3. Save the ZIP file:
   - Choose a location on your computer to save the ZIP file and click Save.

4. Extract the ZIP file:
   - Navigate to the folder where you saved the ZIP file.
   - Right-click on the ZIP file and select Extract All... (Windows) or use your preferred extraction tool.
   - Choose a destination folder and extract the contents.

5. Access the repository:
   - Once extracted, you can access the repository files in the destination folder.

> [!IMPORTANT]
> - No Updates: Keep in mind that downloading the repository as a ZIP file does not allow you to receive updates.    
>   If the repository is updated, you will need to download it again manually.  
> - Ease of Use: This method is simpler and suitable for users who are not comfortable with Git or command-line tools.

# 📝 How to Ask Questions
If you have any questions or issues, you can raise them through the **"Issues"** section of this repository. Here's how you can do it:  

1. Navigate to the **"Issues"** tab at the top of the repository page.  

  ![Issues](Images/Step3.png)

2. Click on the **"New Issue"** button.  
   
  ![New Issue](Images/Step4.png)

3. In the **Title** field, write a short summary of your issue or question.  

4. In the "Description" field, detail your question or issue as thoroughly as possible. You can use text formatting, attach files, and assign the issue to someone if needed. You can also use text formatting (like bullet points or code snippets) for better readability.  

5. Optionally, you can add **labels**, **type**, **projects**, or **milestones** to your issue for better categorization.  

6. Click on the **"Submit new issue"** button to post your question or issue.
   
  ![Submeet New Issue](Images/Step5.png)

I will review and respond to your issue as soon as possible. Your participation helps improve the repository for everyone!  

> [!TIP]
> - Before creating a new issue, please check the **"Closed"** section to see if your question has already been answered.  
>   ![Closed section](Images/Step6.png)  
> - Write your question clearly and respectfully to ensure a faster and better response.  
> - While the examples provided above are in English, feel free to ask your questions in **Persian (فارسی)** as well.  
> - There is no difference in how they will be handled!  

> [!NOTE]
> Pages and interfaces may change over time, but the steps to create an issue generally remain the same.

# 🤝 Contributing to the Repository
To contribute to this repository, please follow these steps:
1. **Fork the Repository**  
2. **Clone the Forked Repository**  
3. **Create a New Branch**  
4. **Make Your Changes**  
5. **Commit Your Changes**  
6. **Push Your Changes to Your Forked Repository**  
7. **Submit a Pull Request (PR)**  

> [!NOTE]
> Please ensure your pull request includes a clear description of the changes you’ve made.
> Once submitted, I will review your contribution and provide feedback if necessary.

# 🌟 Support Me
If you found this repository useful:
- Subscribe to my [YouTube Channel](https://www.youtube.com/@aKaReZa75).
- Share this repository with others.
- Give this repository and my other repositories a star.
- Follow my [GitHub account](https://github.com/aKaReZa75).

# 📜 License
This project is licensed under the GPL-3.0 License. This license grants you the freedom to use, modify, and distribute the project as long as you:
- Credit the original authors: Give proper attribution to the original creators.
- Disclose source code: If you distribute a modified version, you must make the source code available under the same GPL license.
- Maintain the same license: When you distribute derivative works, they must be licensed under the GPL-3.0 too.
- Feel free to use it in your projects, but make sure to comply with the terms of this license.
  
# ✉️ Contact Me
Feel free to reach out to me through any of the following platforms:
- 📧 [Email: aKaReZa75@gmail.com](mailto:aKaReZa75@gmail.com)
- 🎥 [YouTube: @aKaReZa75](https://www.youtube.com/@aKaReZa75)
- 💼 [LinkedIn: @akareza75](https://www.linkedin.com/in/akareza75)
