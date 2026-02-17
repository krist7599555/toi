for pdf in ./*/*/*.pdf; do
  echo $pdf
  pdftotext $pdf
done