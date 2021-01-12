#include<iostream>
#include<string.h>
using namespace std;
//compute lps 
// Fills lps[] for given patttern pat[0..M-1] 
void computeLPSarray(string p,int lps[],int n){
	
	// length of the previous longest prefix suffix 
	
	int i=0;
	int j=1;
	lps[i]=0;// lps[0] is always 0
	while(j<p.size()){
		
		
		if(i==0&&(p[i]!=p[j])){//if (len==0)
			lps[j]=0;
			j++;		
		}
		 
		else if(i>0&&(p[i]!=p[j])){
			i=lps[i-1];		
			
			//  we do not increment 
                // i here 
		}
		else if(p[i]==p[j]){
			lps[j]=i+1;
			i++;
			j++;		
		}
	}

	
}
// Prints occurrences of txt[] in pat[]
void kmpalgorithm(string s,string p){
	int n=s.size();
	
	  // create lps[] that will hold the longest prefix suffix 
    // values for pattern 
	int lps[p.size()];
	// Preprocess the pattern (calculate lps[] array) 
	computeLPSarray(p,lps,n);
	int j=0;//index for pattern
	int i=0;//index for text
	while (i<n) { 
		if(p[j]==s[i]){ 
		    j++; 
		    i++; 
		    //move both pointers forward
		} 
	  
		else if (j==p.size()) { 
		    cout<<"\n Pattern found at: "<<i-j; 
		    j=lps[j-1]; 
		} 
		// mismatch after j matches
		else if(p[j]!=s[i]) { 
			// Do not match lps[0..lps[j-1]] characters, 
            // they will match anyway 
		    if(j==0){//we reach the begining of pattern
				//it means at i we cant find pattern
				//so move i forward to continue find the pattern
			i=i+1;
		    } else{//if we didnt reach begining of pattern
				//we will check for previous value of since till that part 
				//we have already encountered the part of pattern
			j=lps[j-1];
		    }
		} 
       } 
	
}
int main(){
	string s="banananobano";
	string p="nano";
	kmpalgorithm(s,p);
	return 0;
}
