
file="address.txt"

while true
do
    echo "1.Create 2.View 3.Insert 4.Delete 5.Modify 6.Exit"
    read -p "Enter choice: " ch

    case $ch in
        1)
            > "$file"
            echo "Address book created"
            ;;
        2)
            cat "$file"
            ;;
        3)
            read -p "Enter name: " name
            read -p "Enter phone: " phone
            echo "$name $phone" >> "$file"
            ;;
        4)
            read -p "Enter name to delete: " name
            grep -v "^$name " "$file" > temp
            mv temp "$file"
            ;;
        5)
            read -p "Enter name to modify: " name
            grep -v "^$name " "$file" > temp
            read -p "Enter new name: " newname
            read -p "Enter new phone: " phone
            echo "$newname $phone" >> temp
            mv temp "$file"
            ;;
        6)
            exit
            ;;
        *)
            echo "Invalid choice"
            ;;
    esac
done