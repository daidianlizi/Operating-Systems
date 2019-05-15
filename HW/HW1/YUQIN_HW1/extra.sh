echo "Hello World"; pwd
ls; ls |  sort | uniq | wc

(echo "We are inside the subshell.")
echo "Now, We are outside the subshell."

ls>y &