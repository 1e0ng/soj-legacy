//customeize String
//and function trim and isNumberic
String.prototype.trim = function()
{
	return this.replace(/(^\s*)|(\s*$)/g, "");
}
String.prototype.isNumeric = function()
{
	for(i = 0; i < this.length; i++)
	{
		if(this.charAt(i) < '0' || this.charAt(i) > '9')
			return false;
	}
	return true;
}

const invalidChars = "`~!@#$%^&*()-=+\|'\";:/?.>,<";

function hasInvalidChars(str)
{
	for(i = 0; i < invalidChars.length; i++)
	{
		if(str.indexOf(invalidChars.charAt(i)) >= 0)
			return true;
	}
	return false;
}

function isValidUsername(username)
{
	if(username == "")
	{
		alert("Username can't be empty!");
		return false;
	}
	/*Browser has helped us ensure its length
	if(username.length > 32)
	{
		alert("Username is too long!The maximum length is 32.");
		return false;
	}
	*/
	regUsername = /^\w+$/;
	if(!regUsername.test(username))
	{
		alert("Username contains invalid characters.\n" + 
				"Only letters, digits and underscore(_) can be used!");
		return false;
	}
	return true;
}

function isValidEmail(email)
{
	/*
	if(email.length > 128)
	{
		alert("Email address is too long!");
		return false;
	}
	*/
	regEmail = /^(?:\w+\.?)*\w+@(?:\w\.?)*\w$/;
	if(!regEmail.test(email))
	{
		alert("Email is not valid!");
		return false;
	}
	return true;
}

function isValidNickname(nickname)
{
	if(nickname == "")
	{
		alert("Nickname can't be empty!");
		return false;
	}
	/*
	if(nickname.length > 64)
	{
		alert("Nickname is too long!The maximum length is 64");
		return false;
	}
	*/
	if(hasInvalidChars(nickname))
	{
		alert("Nickname contains come invalid characters, such as `~!");
		return false;
	}
	return true;
}

function isValidPasswords(pswd1, pswd2)
{
	if(pswd1 != pswd2)
	{
		alert("The two passwords is not the same!");
		return false;
	}
	if(pswd1 == "" || pswd2 == "")
	{
		alert("Password can't be empty!");
		return false;
	}
	if(pswd1.length < 6)
	{
		alert("Password is too short!");
		return false;
	}
	return true;
}

function checkRegisterItems()
{
	var form = document.forms["formRegister"];
	form["username"].value = form["username"].value.trim();
	form["nickname"].value = form["nickname"].value.trim();
	form["email"].value = form["email"].value.trim();
	if(!isValidUsername(form["username"].value))
	{
		form["username"].focus();
		return false;
	}
	if(!isValidNickname(form["nickname"].value))
	{
		form["nickname"].focus();
		return false;
	}
	if(!isValidPasswords(form["password1"].value, form["password2"].value))
	{
		form["password1"].value = "";
		form["password2"].value = "";
		form["password1"].focus();
		return false;
	}
	if(form["email"].value != "" && !isValidEmail(form["email"].value))
	{
		form["email"].focus();
		return false;
	}
	return true;
}

function checkLoginItems()
{
	form = document.forms["formLogin"];
	if(!isValidUsername(form["username"].value))
	{
		form["username"].focus();
		return false;
	}
	if(form["password"].value == "")
	{
		alert("Password can't be empty!");
		return false;
	}
	return true;
}

function checkSearchProblemItems()
{
	form = document.forms["formSearchProblem"];
	form["pid"].value = form["pid"].value.trim();
	form["title"].value = form["title"].value.trim();
	if(form["pid"].value == "" && form["title"].value == "")
	{
		alert("Problem ID and title can't both be empty!");
		form["pid"].focus();
		return false;
	}
	if(form["pid"].value != "" && !form["pid"].value.isNumeric())
	{
		alert("Problem ID must be a numeral!");
		form["pid"].focus();
		return false;
	}
	return true;
}

function checkSubmitProblemItems()
{
	form = document.forms["formSubmitProblem"];
	form['pid'].value = form['pid'].value.trim();
	if(form['pid'].value == "")
	{
		alert("Problem ID can't be empty!");
		form['pid'].focus();
		return false;
	}
	if(!form['pid'].value.isNumeric())
	{
		alert("Problem ID must be a numeral!");
		form['pid'].focus();
		return false;
	}
	if(form['language'].value == "0")
	{
		alert("Please select a language for your code!");
		return false;
	}
	if(form['source'].value.trim() == "")
	{
		alert("Source code must not be empty!");
		form['source'].focus();
		return false;
	}
	else if(form['source'].value.length > 65535)
	{
		alert("Source code is too long!");
		form['source'].focus();
		return false;
	}
	return true;
}
