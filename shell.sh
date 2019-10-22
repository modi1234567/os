#Shell programming
#Write a program to implement an address book with options given below:
#a) Create address book. b) View address book. c) Insert a record. d) Delete a record.
#e) Modify a record. f) Exit.*/
clear
ch=0;
while (($ch != 6))
do
	echo "                     Menu"
	echo "        1.Create"
	echo "        2.View"
	echo "        3.Insert"
	echo "        4.Modify"
	echo "        5.Delete"
	echo "        6.Exit"
	echo "        Entre Your Choice"
	read ch
	case $ch in
		1)
			echo "        Entre Number of Records"
			read no
			for ((i=0;i<no;i++))
			do
				echo "        Entre Name"
				read name[i]
				echo "        Entre Address"
				read add[i]
				echo "        Enter Phone no"
				read phno[i]
			done 
		;;
		2) 
			echo "        Address Book Recoreds"
			echo "     ------------------------------------"
			for ((i=0;i<no;i++))
			do
				echo "     ------------------"	
				echo "     Record No $((i+1))"
				echo "     ------------------"
				echo "     Name     :   ${name[i]}"
				echo "     Address  :   ${add[i]}"
				echo "     Phone no :   ${phno[i]}"
				echo ""
				echo ""
			done
			echo "     ------------------"
		;;
		3)
			echo "        Enter Where to insert the record"
			read t
 
			t=$((t-1)) 
			temp=$((no-1)) 
			while (($t <= $temp))	
			do
				name[temp+1]=${name[temp]}
				add[temp+1]=${add[temp]}
				phno[temp+1]=$((phno[temp]))
				temp=$((temp-1))
			done
			echo "     Entre Name"
			read name[t]
			echo "     Entre Address"
			read add[t]
			echo "     Enter Phone no"
			read phno[t]
			no=$((no+1))
			echo "     Record Inserted"
		;;
		4)
			echo "        Enter Record Number to modify"
			read t
			t=$((t-1))
			echo "        1.Modify Name"
			echo "        2.Modify Address"
			echo "        3.Modify Phone no"
			read r
			case $r in
				1)
					echo "     Entre Name"
					read name[t]
				;;
				2)
					echo "     Entre Address"
					read add[t]	
				;;
				3)
					echo "     Enter Phone no"
					read phno[t]
				;;
			esac
			echo "     Record Modified"
		;;	
		5)
			echo "       Enter Record Number to delete"
			read t
			t=$((t-1))
			for ((i=t;i<no;i++))
			do
				name[i]=${name[i+1]}
				add[i]=${add[i+1]}
				phno[i]=$((phno[i+1]))
			done
			no=$((no-1))
			echo "        Record Deleted"
		;;
	esac
	echo "        Thank You!"
done 	
#output 
#  aniket@aniket-Inspiron-3521:~/Downloads/os$ chmod +x 1shell.sh
#aniket@aniket-Inspiron-3521:~/Downloads/os$ ./1shell.sh

#                     Menu
#        1.Create
#        2.View
#        3.Insert
#        4.Modify
#        5.Delete
#        6.Exit
#
