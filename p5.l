import re

text = "The quick brown fox jumps over 123 lazy dogs."

token_patterns = [
    (r'(\d+)', 'NUMBER'),            
    (r'([A-Za-z]+)', 'WORD'),        
    (r'\s', 'SPACE'),                
    (r'\.', 'PERIOD'),               
]

tokens = []

for pattern, token_type in token_patterns:
    regex = re.compile(pattern)
    match = regex.match(text)
    while match:
        value = match.group(0)
        tokens.append((value, token_type))
        text = text[len(value):]
        match = regex.match(text)

for token in tokens:
    print(f"Token: {token[0]}, Type: {token[1]}")