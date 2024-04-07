name thor
features:
    - c like style -> comments with // and /*comment*/
      - importieren 
        - #include for c 
        - import [filepath with . as delimiter]
    - optional garbage collector for functions and variables -> attributes marked with @ : @gc
    - keyword yield for return by reference and implicit call to gc
    - dynamic strings with automatic variable insertion -> marked with "", normal strings with '', raw strings with `` ends with space and then \`
      -  format strings like python -> no f"" needed only {} need to be escaped or normal string mode
    - strong typing
    - accept c libraries
    - transpiler pipes to gcc with optimization

