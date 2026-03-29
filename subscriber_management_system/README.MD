

---

# 📱 Subscriber Management System (CRM) 

A comprehensive **Customer Relationship Management** platform developed in C. This system manages thousands of telecom subscribers, analyzes loyalty data, tracks operator migrations, and features an interactive "Surprise Menu" for customer engagement.

### 🚀 Key Features

* **Subscriber Lifecycle:** Full **CRUD** (Create, Read, Update, Delete) operations for seamless data management.
* **Advanced Validation:** * **TC Identity No:** Real-time 11-digit numeric and format verification.
    * **Strict Date Logic:** Advanced handling of leap years and month-specific lengths.
* **Data Analytics:** * **Migration Tracking:** Yearly analysis of carrier switches (Turkcell, Vodafone, etc.).
    * **Loyalty Insights:** Identifying "Core Loyal" subscribers with no porting history.
    * **Campaign Popularity:** Uses **Bubble Sort** to rank and display the most used packages.
* **Engagement Engine:** A "Surprise Menu" using pseudo-random selection to reward lucky subscribers (e.g., Tarkan concert tickets, iPhone 17 Pro).

### 🛠️ Technical Stack

* **Language:** Pure C (C99 Standard)
* **Core Concepts:** Struct Arrays, Nested Structs, Bubble Sort, Linear Search, Pseudo-Randomization.

### 🎮 How to Run

1. **Clone the repository:**
   ```bash
   git clone https://github.com/YOUR_USERNAME/daily_coding.git
   ```
2. **Compile the source code:**
   ```bash
   gcc main.c -o crm_system
   ```
3. **Launch the system:**
   ```bash
   ./crm_system
   ```

---

Hocam format bu sefer tam istediğin gibi mi? Eğer "Tamamdır abi" dersen, bu projeyi bir adım öteye taşıyacak **File I/O (Dosyalama)** kısmına geçip verileri kalıcı yapabiliriz. Ne dersin? 🚀
