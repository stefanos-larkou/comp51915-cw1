#!/bin/bash

interrupt_handler() {
    echo -e "\nReceived Ctrl + C. Exiting..."
    exit 0
}

trap interrupt_handler SIGINT

stop=false

# While the user does not wish to stop
while [ "$stop" = false ]; do
    # Ask user whether they want to run a simulation or the unit tests
    while true; do
        read -p "Do you want to run a simulation or the tests? (s/t): " simtest
        simtest=$(echo "$simtest" | tr '[:upper:]' '[:lower:]')

        if [ "$simtest" = "s" ] || [ "$simtest" = "sim" ] || [ "$simtest" = "simulation" ]; then
            echo "Running simulation."
            break
        elif [ "$simtest" = "t" ] || [ "$simtest" = "test" ] || [ "$simtest" = "tests" ]; then
            echo "Running tests."
            break
        else
            echo "Please enter 's'/'sim'/'simulation' for simulation or 't'/'test'/'tests' for tests."
        fi
    done
    
    # Ask the user whether they want the default values defined in
    # gs.hpp to be used for the simulation/tests or if they want to
    # provide their own values
    while true; do
        read -p "Do you want to use the default values? (y/n): " defcust
        defcust=$(echo "$defcust" | tr '[:upper:]' '[:lower:]')

        if [ "$defcust" = "y" ] || [ "$defcust" = "yes" ]; then
            echo "Running with default values."

            # Run the simulation or the tests depending on what the
            # user previously chose
            if [ "$simtest" = "s" ] || [ "$simtest" = "sim" ] || [ "$simtest" = "simulation" ]; then
                ./build/gs
            else
                ./build/tests/tests
            fi

            break
        elif [ "$defcust" = "n" ] || [ "$defcust" = "no" ]; then
            echo "Running with custom values."

            # In the case that the user chose to run with custom values,
            # need to read Du, Dv, F, k, threshold
            while true; do
                read -p "Du: " Du
                if [[ $Du =~ ^[+-]?[0-9]+\.?[0-9]*$ ]]; then 
                    break; 
                else 
                    echo "All parameters must be real numbers. Enter Du again."; 
                fi
            done

            while true; do
                read -p "Dv: " Dv
                if [[ $Dv =~ ^[+-]?[0-9]+\.?[0-9]*$ ]]; then 
                    break; 
                else 
                    echo "All parameters must be real numbers. Enter Dv again."; 
                fi
            done

            while true; do
                read -p "F: " F
                if [[ $F =~ ^[+-]?[0-9]+\.?[0-9]*$ ]]; then 
                    break; 
                else 
                    echo "All parameters must be real numbers. Enter F again."; 
                fi
            done

            while true; do
                read -p "k: " k
                if [[ $k =~ ^[+-]?[0-9]+\.?[0-9]*$ ]]; then 
                    break; 
                else 
                    echo "All parameters must be real numbers. Enter k again."; 
                fi
            done

            while true; do
                read -p "threshold: " threshold
                if [[ $threshold =~ ^[+-]?[0-9]+\.?[0-9]*$ ]]; then 
                    break; 
                else 
                    echo "All parameters must be real numbers. Enter threshold again."; 
                fi
            done

            # Run the simulation or the tests depending on what the
            # user previously chose, passing the user's parameters
            if [ "$simtest" = "s" ] || [ "$simtest" = "sim" ] || [ "$simtest" = "simulation" ]; then
                ./build/gs $Du $Dv $F $k $threshold
            else
                ./build/tests/tests $Du $Dv $F $k $threshold
            fi

            break
        else
            echo "Please enter 'y'/'yes' for yes or 'n'/'no' for no."
        fi
    done
    
    # Ask the user if they want to keep going, if they say
    # no the script ends, otherwise it starts over
    while true; do
        read -p "Do you want to run another simulation/test? (y/n): " cont
        cont=$(echo "$cont" | tr '[:upper:]' '[:lower:]')

        if [ "$cont" = "y" ] || [ "$cont" = "yes" ]; then
            echo -e "\n"
            break
        elif [ "$cont" = "n" ] || [ "$cont" = "no" ]; then
            stop=true
            break
        else
            echo "Please enter 'y'/'yes' for yes or 'n'/'no' for no."
        fi
    done
done
