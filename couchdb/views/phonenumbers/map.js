function(doc) {  
  if (doc.type && doc.type == "address" && doc.name && doc.mobile) {  
    emit(doc.name, doc.mobile);  
  }  
} 
