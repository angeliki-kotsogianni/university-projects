from calendar import monthrange, month_name
import datetime
import csv

# Βρίσκουμε την τρέχουσα ημερομηνία

now = datetime.datetime.now()
month = now.month
year = now.year
f = open('events.csv', 'w')
f.write('Date,Hour,Duration,Title')
f.write('\n')
f.close()

# Για εμφάνιση των μηνών στα ελληνικά

onoma_mina = []
onoma_mina.append('ΙΑΝ')
onoma_mina.append('ΦΕΒ')
onoma_mina.append('ΜΑΡ')
onoma_mina.append('ΑΠΡ')
onoma_mina.append('ΜΑΪ')
onoma_mina.append('ΙΟΥΝ')
onoma_mina.append('ΙΟΥΛ')
onoma_mina.append('ΑΥΓ')
onoma_mina.append('ΣΕΠ')
onoma_mina.append('ΟΚΤ')
onoma_mina.append('ΝΟΕ')
onoma_mina.append('ΔΕΚ')

# Συνάρτηση για την ανάζητηση γεγονότων

def search():
    print("=== Αναζήτηση γεγονότων ===")
    
    # Ζητάμε από το χρήστη να εισάγει το έτος και το μήνα
    
    flag = True
    while flag == True:
        year = int(input("Εισάγετε έτος:"))
        month = int(input("Εισάγετε μήνα:"))
        if month >= 1 and month <= 12 and year >=2023: # Έλεγχος εγκυρότητας
            flag = False
    
    # Άνοιγμα αρχείου για ανάγνωση και δημιουργία λίστας με τα γεγονότα που αντιστοιχούν στον μήνα προς αναζήτηση
    
    f2 = open('events.csv' , 'r')
    m = 0
    l = []
    for line in f2:
        line = line.strip()
        if line.split('-')[0] == str(year) and line.split('-')[1] == str(month):
            print(str(m) + '.' , '[' + line.split(',')[3] + ']' , '->' , 'Date:' , line.split(',')[0] + ', Time:' , line.split(',')[1] + ', Duration:' , line.split(',')[2])
            m+=1
            l.append(line)
    f2.close()
    return l
 
# Συνάρτηση για την διαχείριση γεγονότων(με την εισαγωγή του'+')   

def manage(nmonth , nyear):
    print("Διαχείριση γεγονότων ημερολογίου")
    print("Επιλέξτε ενέργεια:")
    print("1. Καταγραφή νέου γεγονότος")
    print("2. Διαγραφή γεγονότος")
    print("3. Ενημέρωση γεγονότος")
    print("0. Επιστροφή στο κυρίως μενού")

    choice = input("->")

    if choice == "1":
        
        # Άνοιγμα αρχείου για εγγραφή γεγονότων στο τέλος
        
        f = open('events.csv' , 'a')
         
        flag=True
        while flag==True:
            y = input("Δώσε ημερομηνία σε μορφή YYYY-MM-DD: ")
            x = y.split("-")
            if int(x[0]) > 2022 and int(x[1]) >= 1 and int(x[1]) <= 12 and int(x[2]) >= 1 and int(x[2]) <= monthrange(int(x[0]) , int(x[1]))[1]:
                flag = False
        flag=True
        f.write(y)
        f.write(',')
        while flag==True:
            y = input("Δώσε ώρα γεγoνότος σε μορφή ΗΗ:MM: ")
            z = y.split(":")
            if int(z[0]) <= 23 and int(z[0]) >= 0 and int(z[1]) <= 59 and int(z[1]) >=0 :
                flag = False
        flag=True
        f.write(y)
        f.write(',')
        while flag==True:
            d = int(input("Δώσε διάρκεια γεγονότος: "))
            if d > 0 :
                flag = False
        flag=True
        f.write(str(d))
        f.write(',')
        while flag==True:
            t = input("Δώσε τίτλο γεγονότος: ")
            if isinstance(t , str) and t.count(",")==0 :
                flag = False
        f.write(t)
        f.write('\n')
        f.close()
        manage(nmonth , nyear)
        
    
    elif choice == "2":
        l = search()
        # Άνοιγμα αρχείου για ανάγνωση ώστε να βρεθεί το γεγονός που θέλει να διαγράψει
        f2 = open('events.csv' , 'r')
        x = int(input('Επιλέξτε γεγονός προς διαγραφή:'))
        line_rem = l[x]
        # Δημιουργία λίστας με όλες τις γραμμές για κάθε γεγονός του αρχείου
        l2 = []
        for line in f2:
            line = line.strip()
            l2.append(line)
        f2.close()
        l2.remove(line_rem) # Αφαίρεση του γεγονότος από τη λίστα
        
        # Επανεγγραφή του ενημερωμένου αρχείου
        
        f2 = open('events.csv' , 'w')
        
        for i in range(len(l2)):
            f2.write(l2[i])
            f2.write('\n')
        f2.close()
        manage(nmonth , nyear)
        
    elif choice == "3":
        l = search()
        x = int(input('Επιλέξτε γεγονός προς ενημέρωση:'))
        line_change = l[x]
        temp = l[x].split(',')
        new_date = input('Ημερομηνία γεγονότος ' + '(' +  temp[0] + '):' )
        new_time = input('Ώρα γεγονότος ' + '(' + temp[1] + '):')
        new_duration = input('Διάρκεια γεγονότος ' + '('  + temp[2] + '):')
        new_title = input('Τίτλος γεγονότος ' + '(' + temp[3] + '):')
        # Άνοιγμα αρχείου για ανάγνωση
        f2 = open('events.csv' , 'r')
        # Δημιουργία λίστας με κάθε γραμμή του αρχείου
        l2=[]
        for line in f2:
            line = line.strip()
            l2.append(line)
        f2.close()
        # Επανεγγραφή του αρχείου με ενημερωμένο το γεγονός
        f2 = open('events.csv' , 'w')
        
        # Κάνει τις απαραίτητες αλλαγές σε περίπτωση που χρειάζεται κάθε φορά
        for i in range(len(l2)):
            if l2[i] == line_change:
                if new_date != '':
                    l3 = l2[i].split(',')
                    l3[0] = new_date 
                    l2[i] = ','.join(l3)
                if new_time != '':
                    l3 = l2[i].split(',')
                    l3[1] = new_time 
                    l2[i] = ','.join(l3)
                if new_duration != '':
                    l3 = l2[i].split(',')
                    l3[2] = new_duration 
                    l2[i] = ','.join(l3)
                if new_title != '':
                    l3 = l2[i].split(',')
                    l3[3] = new_title 
                    l2[i] = ','.join(l3)
                print('Το γεγονός ενημερώθηκε:','<'+ '[' + l3[3] + ']' , '->' , 'Date:' , l3[0] + ', Time:' , l3[1] + ', Duration:' , l3[2] ,'>')
            f2.write(l2[i])
            f2.write('\n')
        f2.close()
        manage(nmonth , nyear)
        
    elif choice == "0":
        print("Επιστρέφετε στο κυρίως μενού")
        basic(nmonth , nyear)
        
    else:
        print("Μη έγκυρη επιλογή")
        manage(nmonth , nyear)

# Συνάρτηση που ελέγχει αν η μέρα έχει γεγονός προγραμματισμένο
def gegonos(nmonth , nyear, day):
    x = ' '
    f_check = open('events.csv' , 'r')
    for line in f_check:
        line = line.strip()
        l = line.split(',')
        l2 = l[0].split('-')
        if l2[0] == str(nyear) and l2[1] == str(nmonth) and l2[2] == str(day):
            x = "*"
    f_check.close()
    return x  
    
    
# Συνάρτηση που εμφανίζει τον τρέχοντα μήνα    
def basic(month , year):
    # Βρίσκουμε τον αριθμό των ημερών του μήνα και την ημέρα της εβδομάδας που αρχίζει ο μήνας
    num_days = monthrange(year, month)[1]
    start_day = monthrange(year, month)[0]
    nmonth = month
    nyear = year

    # Βρίσκουμε τον προηγούμενο μήνα και έτος
    prev_month = month - 1
    prev_year = year
    if prev_month == 0:
        prev_month = 12
        prev_year -= 1

    # Βρίσκουμε τον αριθμό των ημερών του προηγούμενου μήνα
    prev_num_days = monthrange(prev_year, prev_month)[1]
    
    print("_________________________________________________")
    print()
    print(f"{onoma_mina[month-1]} {year}")
    print("_________________________________________________")
    print()


    # Εκτυπώνουμε τα γράμματα των ημερών της εβδομάδας
    print("  ΔΕΥ ", end="|")
    print("  ΤΡΙ ", end="|")
    print("  ΤΕΤ ", end="|")
    print("  ΠΕΜ ", end="|")
    print("  ΠΑΡ ", end="|")
    print("  ΣΑΒ ", end="|")
    print("  ΚΥΡ ")



    # Εκτυπώνουμε τα κενά μέρη πριν την πρώτη ημέρα του μήνα
    for i in range(start_day):
        # Εκτυπώνουμε τις ημέρες του προηγούμενου μήνα χωρίς [ ]
        print(f"   {prev_num_days - start_day + i + 1} ", end="|")
    

    # Εκτυπώνουμε τις ημέρες του μήνα
    day = 1
    while day <= num_days:
        if day//10==0:
            if (day + start_day) % 7 != 0:
                print(f" [ {gegonos(nmonth , nyear, day)}{day}]", end="|")
            else:
                print(f" [ {gegonos(nmonth , nyear, day)}{day}]")
        else:
                if (day + start_day) % 7 != 0:
                    print(f" [{gegonos(nmonth , nyear, day)}{day}]", end="|")
                else:
                    print(f" [{gegonos(nmonth , nyear, day)}{day}]")

        day += 1

    
    if month != 12:
        month+=1
    else : 
        month=1
        year+=1
        
    
            
    start_day = monthrange(year, month)[0]
    if start_day!=0:
        for i in range(1 , 8-start_day):
        # Εκτυπώνουμε τις ημέρες του επόμενου μήνα χωρίς [ ]
            if i != 7-start_day:
                print(f"     {i}", end="|")
            else:
                print(f"     {i}")
            


    print()
    print("_________________________________________________")
    print()
    choice = menu()
    # Επεξεργασία της επιλογής του χρήστη
    if choice == "q":
        # Έξοδος από το μενού επιλογών
        return()
    elif choice == "":
        print("Πλοήγηση στον επόμενο μήνα")
        basic(month,year)
    elif choice == "-":
        # Πλοήγηση στον προηγούμενο μήνα
        print("Πλοήγηση στον προηγούμενο μήνα")
        basic(prev_month,prev_year)
    elif choice == "+":
        # Διαχείριση των γεγονότων του ημερολογίου
        print("Διαχείριση των γεγονότων του ημερολογίου")
        manage(nmonth , nyear)
    elif choice == "*":
        search()
        input('Πατήστε οποιοδήποτε χαρακτήρα για επιστροφή στο κυρίως μενού:')
        basic(nmonth , nyear)
    else:
        # Δεν επιλέχθηκε έγκυρη επιλογή, επανέλαβε
        print("Παρακαλώ επιλέξτε μία από τις διαθέσιμες επιλογές")
        basic(nmonth , nyear)
        
# Συνάρτηση για το κύριο μενού επιλογών
def menu():
    # Αρχή του μενού επιλογών
    flag = True
    while flag:
        flag = False
        # Εμφάνιση των επιλογών του μενού
        print("Πατήστε ENTER για προβολή του επόμενου μήνα")
        print("'q' για έξοδο")
        print("'-' για πλοήγηση στον προηγούμενο μήνα")
        print("'+' για διαχείριση των γεγονότων του ημερολογίου")
        print("'*' για εμφάνιση των γεγονότων ενός επιλεγμένου μήνα")
        
        # Ανάγνωση της επιλογής του χρήστη
        choice = input("->")
        return choice

basic(month,year)


