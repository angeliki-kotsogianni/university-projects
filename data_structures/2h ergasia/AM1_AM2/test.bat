javac -d . scr\*.java
java Influenza_k 4 input.txt
java DynamicInfluenza_k_withPQ 4 input.txt
java Dynamic_Median input.txt
del *.class
pause